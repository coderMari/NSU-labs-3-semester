#include "console.h"
#include "field.h"

#include "gtest/gtest.h"

TEST(ConsoleTest, Create_Witout_File) {

	int argc = 1;
	char* argv[10]; 
	argv[0] = { "life.exe" };
	Console a(argc, argv);
	std::vector<int> mas = { 15,15 };
	EXPECT_EQ(a.get_size(), mas);
}

TEST(FieldTest, Create_Witout_File) {

	int argc = 4;
	char* argv[5] = { "./ life.exe", "- f base.lif", "- i 50", "- s 6", "- o a.lif" };
	Console a(argc, argv);
	Field b(a);
	EXPECT_EQ(b.get_name(), "base");
	a.out(b);
	EXPECT_EQ("a.lif", "test.lif");
}