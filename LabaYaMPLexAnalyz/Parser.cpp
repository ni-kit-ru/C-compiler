#pragma once
#include <string>
#include <iostream>
#include "Lexem.cpp"
#include <fstream>
#include <exception>
#include <sstream>
#include "Node.cpp"

using namespace std;

class parcer {
private:
	
	std::string lexem;
	Lexem newLexem;
	void print(std::string str, Node n) {
		cout << str;
	}
	bool isName() {
		for (int a : lexem) {
			if (!(a >= 65 && a <= 90) && !(a >= 97 && a <= 122)) {
				return false;
			}
		}
		return true;
	}
	bool isNum() {
		for (int num : lexem) {
			if (!(num >= 48 && num <= 58)) {
				return false;
			}
		}
		return true;
	}
	void changeLex(string lex) {
		lexem = lex;
		return;
	}

	void Procedure(Node& n)
	{
		
		if (lexem == "procedure")
		{
			print(std::string("Begin"), n);
			n.addNode("Begin");
			Begin(n.getNode(0));
		}
		else {
			throw exception("Wrong input");
		}
		if (lexem == "var" || isName())
		{
			print(std::string("Descriptions"), n);
			n.addNode("Descriptions");
			Descriptions(n.getNode(1));
		}
		else {
			throw exception("Wrong input");
		}
		if (isName())
		{
			print(std::string("Operators"), n);
			n.addNode("Operators");
			Operators(n.getNode(2));
		}
		else {
			throw exception("Wrong input");
		}
		if (lexem == "end")
		{
			print(std::string("End"), n);
			n.addNode("End");
			End(n.getNode(3));
		}
		else {
			throw exception("Wrong input");
		}
		
	}
	void Begin(Node& n) {
		
		if (lexem == "procedure") {
			print(std::string("procedure"), n);
			n.addNode("procedure");
			lexem = newLexem.getNextLexem();
		}
		else {
			throw exception("Wrong input");
		}
		if (isName()) {
			print(std::string("ProcedureName"), n);
			n.addNode("ProcedureName");
			ProcedureName(n.getNode(1));
		}
		else {
			throw exception("Wrong input");
		}
		if (lexem == ";") {
			print(std::string(";"), n);
			n.addNode(";");
			lexem = newLexem.getNextLexem();
		}
		else {
			throw exception("Wrong input");
		}
		if (lexem == "begin") {
			print(std::string("begin"), n);
			n.addNode("begin");
			lexem = newLexem.getNextLexem();
		}
		else {
			throw exception("Wrong input");
		}
		
	}

	void End(Node& n)
	{
		
		if (lexem == "end")
		{
			print(std::string("end"), n);
			n.addNode("end");
			lexem = newLexem.getNextLexem();
		}
		else throw exception("Wrong input");
		
	}

	void ProcedureName(Node& n)
	{
		
		if (isName())
		{
			print(std::string("Id"), n);
			n.addNode("Id");
			Id(n.getNode(0));
		}
		else throw exception("Wrong input");
		
	}

	void Descriptions(Node& n)
	{
		
		if (lexem == "var")
		{
			print(std::string("var"), n);
			n.addNode("var");
			lexem = newLexem.getNextLexem();
		}
		else throw exception("Wrong input");
		if (isName())
		{
			print(std::string("DescrList"), n);
			n.addNode("DescrList");
			DescrList(n.getNode(1));
		}
		else throw exception("Wrong input");
		
	}

	void DescrList(Node& n)
	{
		
		if (isName())
		{
			print(std::string("Descr"), n);
			n.addNode("Descr");
			Descr(n.getNode(0));
		}
		else throw exception("Wrong input");
		if (isName())
		{
			print(std::string("DescrList1"), n);
			n.addNode("DescrList1");
			DescrList1(n.getNode(1));
		}
		else if (lexem == ";") {
			lexem = newLexem.getNextLexem();
			if (lexem == "var") {
				print(std::string("Descriptions"), n);
				n.addNode("Descriptions");
				Descriptions(n.getNode(2));
			}
		}
		else throw exception("Wrong input");
		
	}

	void DescrList1(Node& n) {
		
		if (isName()) {
		}
		else {
			print("eps", n);
			n.addNode("eps");
		}

		
	}

	void Descr(Node& n)
	{
		
		if (isName())
		{
			print(std::string("VarList"), n);
			n.addNode("VarList");
			VarList(n.getNode(0));
		}
		else throw exception("Wrong input");
		if (lexem == ":")
		{
			print(std::string(":"), n);
			n.addNode(":");
			lexem = newLexem.getNextLexem();
		}
		else throw exception("Wrong input");
		if (lexem == "integer")
		{
			print(std::string("Type"), n);
			n.addNode("Type");
			Type(n.getNode(2));
		}
		else throw exception("Wrong input");
		if (lexem == ";")
		{
			print(std::string(";"), n);
			n.addNode(";");
			//lexem = a.getNextLexem();
		}
		else throw exception("Wrong input");
		
	}

	void VarList(Node& n)
	{
		if (isName())
		{
			print(std::string("Id"), n);
			n.addNode("Id");
			Id(n.getNode(0));
		}
		else throw exception("Wrong input");
		if (lexem == ",") {
			print(std::string("VarList1"), n);
			n.addNode("VarList1");
			VarList1(n.getNode(1));
		}
		else throw exception("Wrong input");
		
	}

	void VarList1(Node& n) {

		if (lexem == ",") {
			print(",", n);
			n.addNode(",");

			lexem = newLexem.getNextLexem();
			if (isName()) {
				print("Id", n);
				n.addNode("Id");
				Id(n.getNode(1));
				if (lexem == "," || lexem == ";") {
					print("VarList1", n);
					n.addNode("VarList1");
					Id(n.getNode(2));
				}
				/*
				if (isExtraVars()) {
					print("VarList1", n);
					n.addNode("VarList1");
					VarList1(n.getNode(2));
				}
				*/
			}
			else {
				throw std::exception("Invalid variable declaration");
			}
		}
		else if (lexem == ";") {
			print("eps", n);
			n.addNode("eps");
			lexem = newLexem.getNextLexem();
		}
		else {
			throw std::exception("Invalid");
		}
	}

	void Type(Node& n) {
		
		if (lexem == "integer") {
			print(std::string("integer"), n);
			n.addNode("integer");
			lexem = newLexem.getNextLexem();
		}
		else {
			throw exception("Wrong input");
		}
	}

	void Operators(Node& n)
	{
		
		if (isName() || lexem == "while") {
			print(std::string("Op"), n);
			n.addNode("Op");
			Op(n.getNode(0));
			if (lexem == "end");
			else {
				print(std::string("Operators1"), n);
				n.addNode("Operators1");
				Operators1(n.getNode(1));
			}
		}
		else {
			throw exception("Wrong input");
		}

	}

	void Operators1(Node& n) {

		if (lexem == "end") {
			print("eps", n);
			n.addNode("eps");
		}
		else if (isName() || lexem == "while") {
			print("Op", n);
			n.addNode("Op");
			Op(n.getNode(0));
			print("Operators1", n);
			n.addNode("Operators1");
			Operators1(n.getNode(0));
		}
		else if (lexem == ")") {
			print(")", n);
			n.addNode(")");
		}
		else {
			throw exception("Wrong input");
		}
	
	}

	void Op(Node& n)
	{
		if (lexem == "while") {
			print(std::string("while"), n);
			n.addNode("while");
			lexem = newLexem.getNextLexem();
			if (isName() || lexem == "(") {
				print(std::string("Condition"), n);
				n.addNode("Condition");
				Condition(n.getNode(1));
			}
			else {
				throw exception("Wrong input");
			}
			if (lexem == "do") {
				print(std::string("do"), n);
				n.addNode("do");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}
			if (lexem == "begin") {
				print(std::string("begin"), n);
				n.addNode("begin");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}
			if (isName() || lexem == "while") {
				print(std::string("Operators"), n);
				n.addNode("Operators");
				Operators(n.getNode(4));
			}
			else {
				throw exception("Wrong input");
			}
			if (lexem == "end") {
				print(std::string("end"), n);
				n.addNode("end");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}
			if (lexem == ";") {
				print(std::string(";"), n);
				n.addNode(";");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}

		}
		else if (isName()) {
			print(std::string("Id"), n);
			n.addNode("Id");
			Id(n.getNode(0));
			if (lexem == ":=") {
				print(std::string(":="), n);
				n.addNode(":=");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}
			if (isName() || lexem == "(" || isNum()) {
				print(std::string("Expr"), n);
				n.addNode("Expr");
				Expr(n.getNode(2));
			}
			else {
				throw exception("Wrong input");
			}
			if (lexem == ";") {
				print(std::string(";"), n);
				n.addNode(";");
				lexem = newLexem.getNextLexem();
			}
			else {
				throw exception("Wrong input");
			}
		}
		else {
			throw exception("Wrong input");
		}

	}

	void Expr(Node& n) {
		
		if (isName() || lexem == "(" || isNum()) {
			print(std::string("SimpleExpr"), n);
			n.addNode("SimpleExpr");
			SimpleExpr(n.getNode(0));
		}
		else {
			throw exception("Wrong input");
		}
		if (/*lexem == ";" || */ lexem == "+" || lexem == "-") {
			print(std::string("Expr1"), n);
			n.addNode("Expr1");
			Expr1(n.getNode(1));
		}

	}

	void Expr1(Node& n) {


		if (lexem == "+") {
			print("+", n);
			n.addNode("+");

			lexem = newLexem.getNextLexem();

			print("SimpleExpr", n);
			n.addNode("SimpleExpr");
			SimpleExpr(n.getNode(1));
			/*
			if (isExtraVars()) {
				print("Expr1", n);
				n.addNode("Expr1");
				Expr1(n.getNode(2));
			}
			else {
				print("eps", n);
				n.addNode("eps");
				//lexem = a.getNextLexem();
			}
			*/
		}
		else if (lexem == "-") {
			print("-", n);
			n.addNode("-");

			lexem = newLexem.getNextLexem();

			print("SimpleExpr", n);
			n.addNode("SimpleExpr");
			SimpleExpr(n.getNode(1));
			/*
			if (isExtraVars()) {
				print("Expr1", n);
				n.addNode("Expr1");
				Expr1(n.getNode(2));
			}
			else {
				print("eps", n);
				n.addNode("eps");
			}
			*/
		}
		else {
			print("eps", n);
			n.addNode("eps");
		}

	}

	void SimpleExpr(Node& n) {

		if (isName()) {
			print(std::string("Id"), n);
			n.addNode("Id");
			Id(n.getNode(0));
		}
		else if (lexem == "(") {
			print(std::string("("), n);
			n.addNode("(");
			lexem = newLexem.getNextLexem();
			print(std::string("Expr"), n);
			n.addNode("Expr");
			Expr(n.getNode(1));
			print(std::string(")"), n);
			n.addNode(")");
			lexem = newLexem.getNextLexem();
		}
		else if (isNum()) {
			print(std::string("Const"), n);
			n.addNode("Const");
			Const(n.getNode(0));
		}

		else {
			throw exception("Wrong input");
		}

	}

	void Condition(Node& n) {

		if (isName() || lexem == "(" || isNum()) {
			print(std::string("Expr"), n);
			n.addNode("Expr");
			Expr(n.getNode(0));
		}
		else {
			throw exception("Wrong input");
		}
		if (lexem == "=" || lexem == "<>" || lexem == ">" || lexem == "<") {
			print(std::string("RelationOperator"), n);
			n.addNode("RelationOperator");
			RelationOperator(n.getNode(1));
		}
		else {
			throw exception("Wrong input");
		}
		if (isName() || lexem == "(" || isNum()) {
			print(std::string("Expr"), n);
			n.addNode("Expr");
			Expr(n.getNode(2));
		}
		else {
			throw exception("Wrong input");
		}

	}

	void Id(Node& n) {
	
		print(lexem, n);
		n.addNode(lexem);
		lexem = newLexem.getNextLexem();
		
	}

	void Const(Node& n) {
		
		print(lexem, n);
		n.addNode(lexem);
		lexem = newLexem.getNextLexem();
	
	}

	void RelationOperator(Node& n) {
	
		if (lexem == "=" || lexem == ">" || lexem == "<" || lexem == "<>") {
			print(lexem, n);
			n.addNode(lexem);
			lexem = newLexem.getNextLexem();
		}

	}
};
