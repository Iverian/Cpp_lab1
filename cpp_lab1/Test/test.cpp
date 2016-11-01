#include <gtest/gtest.h>

#include <ANEU_mesh_loader.h>

class ANEU_mesh_loader_test : public testing::Test
{
public:
	static constexpr auto aneu_test_file = "cone.aneu";
};

TEST_F(ANEU_mesh_loader_test, load_mesh_test_1)
{
	ANEU_mesh_loader::instance().load_mesh(aneu_test_file);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}