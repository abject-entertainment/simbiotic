
#include <iostream>
#include "../test.h"
#include "../../src/core/Path.h"

void RunTests()
{
	TestSuite("Testing class: Path");

	//TEST(PathTest, StringConstructor) {
	Test("String Constructor");
	try
	{
		::std::string path = "/a/b/c";
		::simbiotic::Path p(path);
		if (path.compare(p.toString()) == 0)
			{ Succeed(); }
		else
			{ Fail(); }
	}
	catch (::std::invalid_argument &err)
	{
		Fail("Path string constructor threw an exception");
	}
	{
		::simbiotic::Path p("/");
		if (p.size() == 0)
			{ Succeed(); }
		else
			{ Fail("\"" + p.toString() + "\" parsed incorrectly."); }
	}

	Test("Copy Constructor");
	{
		::simbiotic::Path p1("/a/b/c");
		::simbiotic::Path p2(p1);
		if (p1.size() == p2.size())
			{ Succeed(); }
		else
			{ Fail("Size mismatch."); }
		if (p1.toString().compare(p2.toString()) == 0)
			{ Succeed(); }
		else
			{ Fail("\"" + p1.toString() + "\" != \"" + p2.toString() + "\""); }
	}

	Test("Prefix Constructor");
	{
		::simbiotic::Path p(::simbiotic::Path("/a/b/c"), ::simbiotic::Path("/d/e"));
		if (p.toString().compare("/a/b/c/d/e") == 0)
			{ Succeed(); }
		else
			{ Fail("Basic concatenation failed."); }
		::simbiotic::Path p2("/a/b/c", "d");
		if (p2.toString().compare("/a/b/c/d") == 0)
			{ Succeed(); }
		else
			{ Fail("Segment concatenation failed: \"" + p2.toString() + "\" != \"/a/b/c/d\""); }
	}

	Test("size");
	{
		::simbiotic::Path p("/a/b/c/d/e");
		if (p.size() == 5)
			{ Succeed(); }
		else
			{ Fail(); }
		::simbiotic::Path p2("/a/b/../c");
		if (p2.size() == 2)
			{ Succeed(); }
		else
			{ Fail("\"" + p2.toString() + "\" has size " + ::std::to_string(p.size())); }
	}

	Test("isSegment");
	try
	{
		::simbiotic::Path p("a/b/c");
		if (p.isSegment())
			{ Succeed(); }
		else
			{ Fail(); }
	}
	catch (::std::invalid_argument &err)
	{
		Fail("Path string constructor threw an exception");
	}

	Test("isWildcard");
	{
		::simbiotic::Path p("/a/b/c");
		if (p.isWildcard())
			{ Fail(); }
		else
			{ Succeed(); }
		::simbiotic::Path w("/a/*/c");
		if (w.isWildcard())
			{ Succeed(); }
		else
			{ Fail(); }
	}

	Test("hasPrefix");
	{
		::simbiotic::Path p("/a/b/c");
		if (p.hasPrefix(::std::string("/a/b")))
			{ Succeed(); }
		else
			{ Fail(); }
		if (p.hasPrefix(::std::string("/a/c")))
			{ Fail(); }
		else
			{ Succeed(); }
	}

	Test("removePrefix");
	{
		::simbiotic::Path p1("/a/b/c");
		if (p1.removePrefix(::std::string("/d")))
			{ Fail("removePrefix should have returned false"); }
		else
			{ Succeed(); }
		if (p1.removePrefix(::std::string("/a")))
		{
			if (p1.toString().compare(::std::string("/b/c")) == 0)
				{ Succeed(); }
			else
				{ Fail("removePrefix failed: \"" + p1.toString() + "\" != \"/b/c\""); }
		}
		else
			{ Fail("removePrefix should have returned true"); }
	}

	Test("replacePrefix");
	{
		::simbiotic::Path p("/a/b/c");
		if (p.replacePrefix(::std::string("/a/b"), ::std::string("/d")))
		{
			if (p.toString().compare("/d/c") == 0)
				{ Succeed(); }
			else
				{ Fail(); }
		}
		else
			{ Fail(); }
	}

	Test("appendComponent");
	{
		::simbiotic::Path p("/a/b");
		if (p.appendComponent(::std::string("c")))
		{
			if (p.toString().compare("/a/b/c") == 0)
				{ Succeed(); }
			else
				{ Fail(); }
		}
		else
			{ Fail(); }

		::simbiotic::Path p2("/a/b/c");
		if (p2.appendComponent(::std::string("..")))
		{
			if (p2.toString().compare("/a/b") == 0)
				{ Succeed(); }
			else
				{ Fail(); }
		}
		else
			{ Fail(); }

		::simbiotic::Path p3;
		if (p3.appendComponent(::std::string("..")))
			{ Fail("Should have failed: \"" + p3.toString() + "\"(" + ::std::to_string(p3.size()) + ")"); }
		else
			{ Succeed(); }
	}

	Test("matches");
#define TEST_MATCHES(x, y, should_match) { \
	::simbiotic::Path path(::std::string(x)); \
	::simbiotic::Path pattern(::std::string(y)); \
	if (path.matches(pattern) == should_match) \
		{ Succeed(); } \
	else \
		{ Fail("\"" + path.toString() + "\" vs. \"" + pattern.toString() + "\""); } \
}

	TEST_MATCHES("/a/b/c", "/a/b/c", true)
	TEST_MATCHES("/a/b/c", "/a/*/c", true)
	TEST_MATCHES("/a/b/c", "/**/c", true)


	Test("matchesPrefix");
#define TEST_PREFIX(x, y, should_match) { \
	::simbiotic::Path path(::std::string(x)); \
	::simbiotic::Path pattern(::std::string(y)); \
	if (path.matchesPrefix(pattern) == should_match) \
		{ Succeed(); } \
	else \
		{ Fail("\"" + path.toString() + "\" vs. \"" + pattern.toString() + "\""); } \
}

	TEST_PREFIX("/a/b/c", "/a/b", true)
	TEST_PREFIX("/a/b/c", "/*/b", true)
	TEST_PREFIX("/a/b/c", "/**/b", true)

}