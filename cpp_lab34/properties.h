#pragma once

#define prop_ static constexpr auto

prop_ filenameRegex = "[^\\\\/:*<>|]+(\\.(\\w+))?";			 //[^\\/:*<>|]+(\.(\w+))?
prop_ absolutePathRegex = "(.+)/([^\\\\/:*<>|]+(\\.\\w+)?)"; //(.+)/(filenameRegex)
prop_ fileIconPath = ":/icons/icons/file.png";
prop_ exclamationIconPath = ":/icons/icons/exclamation.png";

prop_ syntaxRulesDir = "./syntax";
prop_ syntaxFileMask = "?*.syntax";
prop_ syntaxFileRegEx = "(.+)\\.syntax";

prop_ fontName = "Courier New";
