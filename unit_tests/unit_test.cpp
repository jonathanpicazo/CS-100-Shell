//unit tests
#include "Argument.hpp"
#include "Parse.hpp"
#include "gtest/gtest.h"
#include <string>
#include "Connector.hpp"
#include "Paranthesis.hpp"
#include "CommandTable.hpp"
using namespace std;
//Argument Class Tests
TEST (StringArgumentTest, ExpectParse1) 
{
	string input = "ls -a";
	Argument* tester = new Argument(input);
	tester->parse();
	EXPECT_EQ(tester->at(0), "ls");
	EXPECT_EQ(tester->at(1), "-a");
}

TEST (StringArgumentTest, ExpectParse2) 
{
	string input = "git branch";
	Argument* tester = new Argument(input);
	tester->parse();
	EXPECT_EQ(tester->at(0), "git");
	EXPECT_EQ(tester->at(1), "branch");
}

TEST (StringArgumentTest, ExpectParseLong) 
{
	string input = "echo this is a really long string to echo";
	Argument* tester = new Argument(input);
	tester->parse();
	EXPECT_EQ(tester->at(0), "echo");
	EXPECT_EQ(tester->at(1), "this");
	EXPECT_EQ(tester->at(2), "is");
	EXPECT_EQ(tester->at(3), "a");
	EXPECT_EQ(tester->at(4), "really");
	EXPECT_EQ(tester->at(5), "long");
	EXPECT_EQ(tester->at(6), "string");
	EXPECT_EQ(tester->at(7), "to");
	EXPECT_EQ(tester->at(8), "echo");
}
//Connector Class Test
//Semicolon
TEST(ConnectorTest, TwoSemicolon) {
	string input = "git branch; git master";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "git");
	EXPECT_EQ(cr->at(0)->at(1), "branch");
	EXPECT_EQ(cr->at(1)->at(0), "git");
	EXPECT_EQ(cr->at(1)->at(1), "master");
}

TEST(ConnectorTest, FiveSemiColon) {
	string input = "ls -a; git branch; git master; echo Hello World; ls -l";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "ls");
	EXPECT_EQ(cr->at(0)->at(1), "-a");
	EXPECT_EQ(cr->at(1)->at(0), "git");
	EXPECT_EQ(cr->at(1)->at(1), "branch");
	EXPECT_EQ(cr->at(2)->at(0), "git");
	EXPECT_EQ(cr->at(2)->at(1), "master");
	EXPECT_EQ(cr->at(3)->at(0), "echo");
	EXPECT_EQ(cr->at(3)->at(1), "Hello");
	EXPECT_EQ(cr->at(3)->at(2), "World");
	EXPECT_EQ(cr->at(4)->at(0), "ls");
	EXPECT_EQ(cr->at(4)->at(1), "-l");
	ASSERT_EQ(cr->size(), 5);
}
//And
TEST(ConnectorTest, TwoAnd) {
	string input = "echo really long long long string && ls -a";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "really");
	EXPECT_EQ(cr->at(0)->at(2), "long");
	EXPECT_EQ(cr->at(0)->at(3), "long");
	EXPECT_EQ(cr->at(0)->at(4), "long");
	EXPECT_EQ(cr->at(0)->at(5), "string");
	EXPECT_EQ(cr->at(1)->at(0), "ls");
	EXPECT_EQ(cr->at(1)->at(1), "-a");
	ASSERT_EQ(cr->size(), 2);
}

TEST(ConnectorTest, LongAnd) {
	string input = "echo really long long long string && ls -a && git branch && echo hello world && git status";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "really");
	EXPECT_EQ(cr->at(0)->at(2), "long");
	EXPECT_EQ(cr->at(0)->at(3), "long");
	EXPECT_EQ(cr->at(0)->at(4), "long");
	EXPECT_EQ(cr->at(0)->at(5), "string");
	EXPECT_EQ(cr->at(1)->at(0), "ls");
	EXPECT_EQ(cr->at(1)->at(1), "-a");
	EXPECT_EQ(cr->at(2)->at(0), "git");
	EXPECT_EQ(cr->at(2)->at(1), "branch");
	EXPECT_EQ(cr->at(3)->at(0), "echo");
	EXPECT_EQ(cr->at(3)->at(1), "hello");
	EXPECT_EQ(cr->at(3)->at(2), "world");
	EXPECT_EQ(cr->at(4)->at(0), "git");
	EXPECT_EQ(cr->at(4)->at(1), "status");
	ASSERT_EQ(cr->size(), 5);
}
//Or
TEST(ConnectorTest, TwoOr) {
	string input = "echo really long long long string || echo hope this works";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "really");
	EXPECT_EQ(cr->at(0)->at(2), "long");
	EXPECT_EQ(cr->at(0)->at(3), "long");
	EXPECT_EQ(cr->at(0)->at(4), "long");
	EXPECT_EQ(cr->at(0)->at(5), "string");
	EXPECT_EQ(cr->at(1)->at(0), "echo");
	EXPECT_EQ(cr->at(1)->at(1), "hope");
	EXPECT_EQ(cr->at(1)->at(2), "this");
	EXPECT_EQ(cr->at(1)->at(3), "works");
	ASSERT_EQ(cr->size(), 2);
}

TEST(ConnectorTest, LongOr) {
	string input = "echo really long long long string || ls -a || git branch || echo hello world || git status";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "really");
	EXPECT_EQ(cr->at(0)->at(2), "long");
	EXPECT_EQ(cr->at(0)->at(3), "long");
	EXPECT_EQ(cr->at(0)->at(4), "long");
	EXPECT_EQ(cr->at(0)->at(5), "string");
	EXPECT_EQ(cr->at(1)->at(0), "ls");
	EXPECT_EQ(cr->at(1)->at(1), "-a");
	EXPECT_EQ(cr->at(2)->at(0), "git");
	EXPECT_EQ(cr->at(2)->at(1), "branch");
	EXPECT_EQ(cr->at(3)->at(0), "echo");
	EXPECT_EQ(cr->at(3)->at(1), "hello");
	EXPECT_EQ(cr->at(3)->at(2), "world");
	EXPECT_EQ(cr->at(4)->at(0), "git");
	EXPECT_EQ(cr->at(4)->at(1), "status");
	ASSERT_EQ(cr->size(), 5);
}
//AndOrSemi
TEST(ConnectorTest, AndOrSemi) {
	string input = "echo really long long long string ; ls -a || git branch && echo hello world ; git status || ls -l";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "really");
	EXPECT_EQ(cr->at(0)->at(2), "long");
	EXPECT_EQ(cr->at(0)->at(3), "long");
	EXPECT_EQ(cr->at(0)->at(4), "long");
	EXPECT_EQ(cr->at(0)->at(5), "string");
	EXPECT_EQ(cr->at(1)->at(0), "ls");
	EXPECT_EQ(cr->at(1)->at(1), "-a");
	EXPECT_EQ(cr->at(2)->at(0), "git");
	EXPECT_EQ(cr->at(2)->at(1), "branch");
	EXPECT_EQ(cr->at(3)->at(0), "echo");
	EXPECT_EQ(cr->at(3)->at(1), "hello");
	EXPECT_EQ(cr->at(3)->at(2), "world");
	EXPECT_EQ(cr->at(4)->at(0), "git");
	EXPECT_EQ(cr->at(4)->at(1), "status");
	EXPECT_EQ(cr->at(5)->at(0), "ls");
	EXPECT_EQ(cr->at(5)->at(1), "-l");
	ASSERT_EQ(cr->size(), 6);
}
//Comment
TEST(ConnectorTest, CommandFollowingComment) {
	string input = "git branch #this is a comment";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "git");
	EXPECT_EQ(cr->at(0)->at(1), "branch");
	ASSERT_EQ(cr->size(), 1);
}

TEST(ConnectorTest, MultiFollowingComment) {
	string input = "git branch; ls -a; echo Hello World #this is a comment";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "git");
	EXPECT_EQ(cr->at(0)->at(1), "branch");
	EXPECT_EQ(cr->at(1)->at(0), "ls");
	EXPECT_EQ(cr->at(1)->at(1), "-a");
	EXPECT_EQ(cr->at(2)->at(0), "echo");
	EXPECT_EQ(cr->at(2)->at(1), "Hello");
	EXPECT_EQ(cr->at(2)->at(2), "World");
	ASSERT_EQ(cr->size(), 3);
}
TEST(ConnectorTest, CommentBeforeCommands) {
	string input = "#comment before some commands, git branch; ls -a; echo Hello World #this is a comment";
	Connector* cr = new Connector(input);
	cr->parse();
	ASSERT_EQ(cr->size(), 0);
}

TEST(QuoteTest, CommandInQuote) {
	string input = "echo \"ls -a\"";
	Connector* cr = new Connector(input);
	cr->parse();
	EXPECT_EQ(cr->at(0)->at(0), "echo");
	EXPECT_EQ(cr->at(0)->at(1), "ls");
	EXPECT_EQ(cr->at(0)->at(2), "-a");
}

TEST(PrecedenceTest, WithoutParen) {
	string input = "echo hello world ; echo \"ayo ls -a\"; git branch";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "hello");
	EXPECT_EQ(pr->at(0)->at(0)->at(2), "world");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "ayo");
	EXPECT_EQ(pr->at(0)->at(1)->at(2), "ls");
	EXPECT_EQ(pr->at(0)->at(1)->at(3), "-a");
	EXPECT_EQ(pr->at(0)->at(2)->at(0), "git");
	EXPECT_EQ(pr->at(0)->at(2)->at(1), "branch");
	ASSERT_EQ(pr->size(), 1);
}

TEST(PrecedenceTest, OneParenthesisSemiConnector) {
	string input = "(echo hello world) ; (ls -a)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "hello");
	EXPECT_EQ(pr->at(0)->at(0)->at(2), "world");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	ASSERT_EQ(pr->size(), 2);
}
TEST(PrecedenceTest, OneParenthesisAllConnectors) {
	string input = "(echo hello world) ; (ls -a) && (git branch) || (ls -l)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "hello");
	EXPECT_EQ(pr->at(0)->at(0)->at(2), "world");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	EXPECT_EQ(pr->at(2)->at(0)->at(0), "git");
	EXPECT_EQ(pr->at(2)->at(0)->at(1), "branch");
	EXPECT_EQ(pr->at(3)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(3)->at(0)->at(1), "-l");
	ASSERT_EQ(pr->size(), 4);
}

TEST(PrecedenceTest, GitHubTest) {
	string input = "(echo A && echo B) ; (echo C && echo D)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "C");
	EXPECT_EQ(pr->at(1)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(1)->at(1)->at(1), "D");
	ASSERT_EQ(pr->size(), 2);
}
TEST(PrecedenceTest, CommentTest) {
	string input = "(echo A && echo B)# ; (echo C && echo D)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	ASSERT_EQ(pr->size(), 1);
}
TEST(PrecedenceTest, InitialCommentTest) {
	string input = "#(echo A && echo B)# ; (echo C && echo D)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	ASSERT_EQ(pr->size(), 0);
}
TEST(PrecedenceTest, QuoteOneParenTest) {
	string input = "echo \"(random command # ls -a || git branch)\"";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "(random");
	EXPECT_EQ(pr->at(0)->at(0)->at(2), "command");
	EXPECT_EQ(pr->at(0)->at(0)->at(3), "#");
	EXPECT_EQ(pr->at(0)->at(0)->at(4), "ls");
	EXPECT_EQ(pr->at(0)->at(0)->at(5), "-a");
	EXPECT_EQ(pr->at(0)->at(0)->at(6), "||");
	EXPECT_EQ(pr->at(0)->at(0)->at(7), "git");
	EXPECT_EQ(pr->at(0)->at(0)->at(8), "branch)");
	ASSERT_EQ(pr->size(), 1);
}
TEST(PrecedenceTest, ParenAfterNormal) {
	string input = "git branch; (echo A && echo B)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "git");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "branch");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(1)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(1)->at(1)->at(1), "B");
	ASSERT_EQ(pr->size(), 2);
}

TEST(PrecedenceTest, CommandAfterParen) {
	string input = "(echo A && echo B) ; ls -a";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	ASSERT_EQ(pr->size(), 2);
}

TEST(PrecedenceTest, SemiInParen) {
	string input = "(echo A ; echo B) ; ls -a";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	ASSERT_EQ(pr->size(), 2);
}

TEST(PrecedenceTest, CommandBetweenTwoParenSemi) {
	string input = "(echo A && echo B) ; ls -a ; (echo C || echo D)";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	EXPECT_EQ(pr->at(2)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(0)->at(1), "C");
	EXPECT_EQ(pr->at(2)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(1)->at(1), "D");
	ASSERT_EQ(pr->size(), 3); 
}

TEST(PrecedenceTest, CommandBetweenTwoParenSemi2) {
	string input = "(echo A && echo B) ; ls -a ; (echo C ||echo D); git branch && ls -l";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(0)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(0)->at(1)->at(1), "B");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "-a");
	EXPECT_EQ(pr->at(2)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(0)->at(1), "C");
	EXPECT_EQ(pr->at(2)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(1)->at(1), "D");
	EXPECT_EQ(pr->at(3)->at(0)->at(0), "git");
	EXPECT_EQ(pr->at(3)->at(0)->at(1), "branch");
	EXPECT_EQ(pr->at(4)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(4)->at(0)->at(1), "-l");
	ASSERT_EQ(pr->size(), 5); 
}
TEST(PrecedenceTest, FinalTest) {
	string input = "ls -a && git branch || (echo A ; echo D); echo \"this is () scuffed\"";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "ls");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), "-a");
	EXPECT_EQ(pr->at(1)->at(0)->at(0), "git");
	EXPECT_EQ(pr->at(1)->at(0)->at(1), "branch");
	EXPECT_EQ(pr->at(2)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(0)->at(1), "A");
	EXPECT_EQ(pr->at(2)->at(1)->at(0), "echo");
	EXPECT_EQ(pr->at(2)->at(1)->at(1), "D");
	EXPECT_EQ(pr->at(3)->at(0)->at(0), "echo");
	EXPECT_EQ(pr->at(3)->at(0)->at(1), "this");
	EXPECT_EQ(pr->at(3)->at(0)->at(2), "is");
	EXPECT_EQ(pr->at(3)->at(0)->at(3), "()");
	EXPECT_EQ(pr->at(3)->at(0)->at(4), "scuffed");
	EXPECT_EQ(pr->size(), 4);
}


TEST(PipeTest, InitParsingTest) {
	string input =  "cat > existingfile.txt";
	Paranthesis* pr = new Paranthesis(input);
	pr->parse();
	EXPECT_EQ(pr->at(0)->at(0)->at(0), "cat");
	EXPECT_EQ(pr->at(0)->at(0)->at(1), ">");
	EXPECT_EQ(pr->at(0)->at(0)->at(2), "existingfile.txt");
	ASSERT_EQ(pr->size(),1);
}

TEST(PipeTest, RedirectionParseTest) {
	string input = "ls -a >> lol.txt";
	Argument* ps = new Argument(input);
	ps->parse();
	CommandTable* ct = new CommandTable(input);
	ct->redirection_parse(ps->retVect());
	EXPECT_EQ(ct->redirection_parse(ps->retVect()), 2);
}




//test with || and && instead of ; separating the statements in between paranthesis





int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
