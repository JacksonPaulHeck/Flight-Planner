//
// Created by jacks on 4/8/2020.
//

#include "catch.hpp"
#include "JPStack.h"

TEST_CASE("JPLinkedList Testing"){
    SECTION("JPLinkedList Test"){
        JPLinkedList<int> jpLinkedList;
        jpLinkedList.append(0);
        jpLinkedList.append(1);
        jpLinkedList.append(2);
        jpLinkedList.append(3);
        jpLinkedList.append(4);
        jpLinkedList.append(5);

        REQUIRE(jpLinkedList.contains(0));
        REQUIRE(jpLinkedList.contains(1));
        REQUIRE(jpLinkedList.contains(2));
        REQUIRE(jpLinkedList.contains(3));
        REQUIRE(jpLinkedList.contains(4));
        REQUIRE(jpLinkedList.contains(5));

        REQUIRE(jpLinkedList.length() == 6);

        REQUIRE(!jpLinkedList.isEmpty());

        jpLinkedList.remove();

        REQUIRE(jpLinkedList.length() == 5);

        jpLinkedList.insert(-1);

        REQUIRE(jpLinkedList.length() == 6);
    }
}

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