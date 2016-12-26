#include "Calculator.h"
#include "Symbol.h"
#include "utility.h"

#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QLCDNumber>
#include <QRadioButton>

#define DISPLAY display(data.cur().num)

QLayout* setupEng(
	QWidget* disp, QWidget* box, QWidget* clear, QWidget* left, QWidget* right);
QLayout* setupBase(QWidget* disp, QWidget* box, QWidget* clear, QWidget* right);
QWidget* setupHeader(QWidget* disp, QWidget* box, QWidget* clear, int col);

int Calculator::binaryPrior(int operId)
{
	int retval = -1;
	switch (operId) {
	case TOK::PLUS:
	case TOK::MINUS:
		retval = 0;
		break;
	case TOK::MULT:
	case TOK::DIV:
		retval = 1;
		break;
	case TOK::POWER:
	case TOK::ROOT:
	case TOK::LOG:
		retval = 2;
		break;
	default:
		break;
	}
	return retval;
}

Calculator::Internal::Internal()
	: stack()
	, curPrior(0)
{
	for (auto i = 0; i != stackSize; ++i)
		stack[i] = {0., 0};
}

Calculator::Pair& Calculator::Internal::cur()
{
	return empty() ? stack[++curPrior] : stack[curPrior];
}

Calculator::Pair& Calculator::Internal::at(int id) { return stack[id]; }

void Calculator::Internal::pop()
{
	if (curPrior != -1)
		stack[curPrior--] = {0., 0};
}

void Calculator::Internal::eval()
{
	if (curPrior != 0) {
		if (stack[curPrior - 1].operId > 0) {
			stack[curPrior - 1].num = applyBinary(stack[curPrior - 1].num,
				stack[curPrior].num, stack[curPrior - 1].operId);
			stack[curPrior].num = 0.;
		} else
			stack[curPrior - 1].num = stack[curPrior].num;
		stack[curPrior - 1].operId = 0;
		--curPrior;
	} else
		stack[curPrior].operId = 0;
}

void Calculator::Internal::push()
{
	if (curPrior != stackSize - 1)
		++curPrior;
}

void Calculator::Internal::fetchLeftOperand()
{
	if (qFuzzyCompare(stack[curPrior].num, 0.))
		for (auto i = curPrior - 1; i != -1; --i) {
			stack[i].operId = 0;
			if (!qFuzzyCompare(stack[i].num, 0.)) {
				stack[curPrior].num = stack[i].num;
				stack[i].num = 0.;
				break;
			}
		}
}

bool Calculator::Internal::empty() { return curPrior == -1; }

Calculator::Calculator(QWidget* parent)
	: QWidget(parent)
	, data()
	, expectingOperator(false)
	, current(mode::NORMAL)
	, resultDisplay(Q_NULLPTR)
	, buttonBox(Q_NULLPTR)
	, clearButton(Q_NULLPTR)
	, baseButtons(Q_NULLPTR)
	, engButtons(Q_NULLPTR)
{
	setupLayout();
	changeMode((int)current);
}

void Calculator::changeMode(int modeId)
{
	delete layout();
	if ((mode)modeId == mode::NORMAL) {
		engButtons->hide();
		setLayout(setupBase(resultDisplay, buttonBox, clearButton, baseButtons));
	} else {
		engButtons->show();
		setLayout(
			setupEng(resultDisplay, buttonBox, clearButton, engButtons, baseButtons));
	}
	setWindowTitle(windowTitle(current = (mode)modeId));
}

void Calculator::binary()
{
	auto buttonId = qobject_cast<Button*>(sender())->id();
	auto prior = binaryPrior(buttonId);

	if (prior == -1)
		return;

	if (prior >= data.curPrior) {
		data.curPrior = prior;
		data.fetchLeftOperand();
		data.cur().operId = buttonId;
		++data.curPrior;
	} else if (prior < data.curPrior) {
		while (data.curPrior != prior)
			data.eval();
		data.cur().operId = buttonId;

		DISPLAY;
		expectingOperator = true;

		data.curPrior++;
	}
}

void Calculator::equal()
{
	while (data.curPrior != 0)
		data.eval();

	expectingOperator = true;
	DISPLAY;
}

void Calculator::clear()
{
	while (!data.empty())
		data.pop();

	expectingOperator = false;
	DISPLAY;
}

void Calculator::unary()
{
	auto buttonId = qobject_cast<Button*>(sender())->id();
	auto& num = data.cur().num;
	data.cur().operId = 0;
	expectingOperator = true;

	switch ((token)buttonId) {
	case token::INVERSE:
		num = 1. / num;
		break;
	case token::SQROOT:
		num = sqrt(num);
		break;
	case token::SQUARE:
		num = pow(num, 2.);
		break;
	case token::CUBE:
		num = pow(num, 3.);
		break;
	case token::EXP:
		num = exp(num);
		break;
	case token::LN:
		num = log(num);
		break;
	case token::CUBEROOT:
		num = pow(num, 1. / 3);
		break;
	case token::SIN:
		num = sin(num);
		break;
	case token::COS:
		num = cos(num);
		break;
	case token::TAN:
		num = tan(num);
		break;
	case token::PI:
		num = acos(-1);
		break;
	case token::SINH:
		num = sinh(num);
		break;
	case token::COSH:
		num = cosh(num);
		break;
	case token::TANH:
		num = tanh(num);
		break;
	case token::FACT:
		num = fact(num);
		break;
	default:
		break;
	}
	DISPLAY;
}

void Calculator::point()
{
	if (expectingOperator) {
		data.cur() = {0., 0};
		expectingOperator = false;
	}
	data.cur().operId = -10;
	DISPLAY;
}

void Calculator::changeSign()
{
	data.cur().num *= -1;
	DISPLAY;
}

#define SIGN(x) (((x) < 0) ? (-1) : (1))

void Calculator::digit()
{
	auto buttonId = qobject_cast<Button*>(sender())->id();
	if (expectingOperator) {
		data.cur() = {0., 0};
		expectingOperator = false;
	}
	if (data.cur().operId >= 0)
		data.cur().num = data.cur().num * 10 + SIGN(data.cur().num) * buttonId;
	else {
		data.cur().num = data.cur().num
			+ SIGN(data.cur().num) * double(buttonId) / abs(data.cur().operId);
		data.cur().operId *= 10;
	}
	DISPLAY;
}

void Calculator::setupLayout()
{
	resultDisplay = new QLCDKostil(id::maxDigitCount);
	connect(this, SIGNAL(display(double)), resultDisplay, SLOT(display(double)));

	auto selector = new QButtonGroup(this);
	auto normalModeButton = new QRadioButton(str::normalMode);
	auto engineerModeButton = new QRadioButton(str::engineerMode);
	selector->addButton(normalModeButton, (int)mode::NORMAL);
	selector->addButton(engineerModeButton, (int)mode::ENGINEER);
	normalModeButton->click();
	connect(selector, SIGNAL(buttonClicked(int)), this, SLOT(changeMode(int)));

	buttonBox = new QGroupBox;
	auto radioButtonLayout = new QVBoxLayout;
	radioButtonLayout->addWidget(normalModeButton);
	radioButtonLayout->addWidget(engineerModeButton);
	buttonBox->setLayout(radioButtonLayout);

	clearButton = createButton((int)token::CLEAR, SLOT(clear()));

	buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	clearButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

	engButtons = setupEngButtons();
	engButtons->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	baseButtons = setupBaseButtons();
	baseButtons->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QWidget* setupHeader(QWidget* disp, QWidget* box, QWidget* clear, int col)
{
	auto layout = new QGridLayout;

	layout->addWidget(disp, 0, 0, 2, col);
	layout->addWidget(box, 2, 0, 1, col - 1);
	layout->addWidget(clear, 2, col - 1);

	auto wid = new QWidget;
	wid->setLayout(layout);
	return wid;
}

QLayout* setupEng(
	QWidget* disp, QWidget* box, QWidget* clear, QWidget* left, QWidget* right)
{
	auto layout = new QGridLayout;
	layout->setSizeConstraint(QLayout::SetFixedSize);

	layout->addWidget(setupHeader(disp, box, clear, 9), 0, 0, 2, 9);
	layout->addWidget(left, 2, 0, 4, 4);
	layout->addWidget(right, 2, 4, 4, 5);

	return layout;
}

QLayout* setupBase(QWidget* disp, QWidget* box, QWidget* clear, QWidget* right)
{
	auto layout = new QGridLayout;
	layout->setSizeConstraint(QLayout::SetFixedSize);

	layout->addWidget(setupHeader(disp, box, clear, 5), 0, 0, 2, 5);
	layout->addWidget(right, 2, 0, 4, 5);

	return layout;
}

QWidget* Calculator::setupEngButtons()
{
	Button* optionalButton[(int)token::FACT - TOK::SQUARE + 1];
	auto layout = new QGridLayout;
	for (auto i = 0; i != TOK::FACT - TOK::SQUARE + 1; ++i) {
		optionalButton[i] = createButton(TOK::SQUARE + i,
			(i != TOK::POWER - TOK::SQUARE && i != TOK::ROOT - TOK::SQUARE
				&& i != TOK::LOG - TOK::SQUARE)
				? SLOT(unary())
				: SLOT(binary()));
		layout->addWidget(optionalButton[i], i % id::ColumnDelta,
			id::ColumnDelta - 1 - i / id::ColumnDelta);
	}
	auto wid = new QWidget();
	wid->setLayout(layout);
	return wid;
}

QWidget* Calculator::setupBaseButtons()
{
	auto layout = new QGridLayout;

	auto pointButton = createButton(TOK::POINT, SLOT(point()));
	auto equalButton = createButton(TOK::EQUAL, SLOT(equal()));
	auto inverseButton = createButton(TOK::INVERSE, SLOT(unary()));
	auto squareRootButton = createButton(TOK::SQROOT, SLOT(unary()));
	auto changeSignButton = createButton(TOK::CHANGE_SIGN, SLOT(changeSign()));

	Button* binaryButton[TOK::PLUS - TOK::DIV + 1];
	for (auto i = 0; i != TOK::PLUS - TOK::DIV + 1; ++i)
		binaryButton[i] = createButton(TOK::DIV + i, SLOT(binary()));

	Button* digitButton[id::magicNumber];
	for (auto i = 0; i != id::magicNumber; ++i)
		digitButton[i] = createButton(i, SLOT(digit()));

	layout->addWidget(squareRootButton, 0, 5);
	layout->addWidget(inverseButton, 1, 5);
	layout->addWidget(equalButton, 2, 5, 2, 1);
	layout->addWidget(changeSignButton, 3, 0);

	for (auto i = 0; i != TOK::PLUS - TOK::DIV + 1; ++i)
		layout->addWidget(binaryButton[i], i, 4);

	layout->addWidget(pointButton, 3, 2);
	layout->addWidget(digitButton[0], 3, 1);

	for (auto i = 1; i != id::magicNumber; ++i)
		layout->addWidget(digitButton[i], (i - 1) / 3, (i - 1) % 3);

	auto wid = new QWidget;
	wid->setLayout(layout);
	return wid;
}

Button* Calculator::createButton(int id, const char* slot)
{
	auto button = new Button(id);
	connect(button, SIGNAL(clicked()), this, slot);
	return button;
}

QString Calculator::windowTitle(mode id) const
{
	return QString("%1(%2)").arg(
		str::windowTitle, id == mode::NORMAL ? str::normalMode : str::engineerMode);
}

QSize QLCDKostil::sizeHint() const
{
	auto size = QLCDNumber::sizeHint();
	size.rheight() += 20;
	return size;
}
