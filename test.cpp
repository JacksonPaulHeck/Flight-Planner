//
// Created by jacks on 4/8/2020.
//

#include "catch.hpp"
#include "JPStack.h"

//Tests for JPStack

TEST_CASE("JPStack Testing") {
    JPString jpString("JPString");
    SECTION("Empty Constructor and isEmpty") {
        JPStack jpStack;
        REQUIRE(jpStack.isEmpty());
    }SECTION("Clear Function") {
        JPStack jpStack;
        jpStack.push(jpString);
        jpStack.push(jpString);
        jpStack.clear();
        REQUIRE(jpStack.isEmpty());
    }SECTION("Push & Peek") {
        JPStack jpStack;
        jpStack.push(jpString);
        REQUIRE(jpStack.peek() == jpString);
    }SECTION("Pop") {
        JPStack jpStack;
        jpStack.push(jpString);
        REQUIRE(jpStack.pop() == jpString);
        REQUIRE(jpStack.isEmpty());
    }SECTION("Length"){
        JPStack jpStack;
        jpStack.push(jpString);
        REQUIRE(jpStack.length() == 1);
    }SECTION("Contains"){
        JPStack jpStack;
        jpStack.push(jpString);
        REQUIRE(jpStack.contains(jpString));
    }
}