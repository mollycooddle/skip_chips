//
// Created by Софья Фролова  on 21.10.2024.
//
#include "list.h"
#include <gtest.h>
TEST(List, can_create_empty_list)
{
ASSERT_NO_THROW(List<int> L1());
}
//
TEST(List, can_create_copy_list)
{
    List<int> L1(1);
    List<int> L2 = L1;
    ASSERT_EQ(L1, L2);

}

TEST(List, can_create_list_with_parameters)
{
    ASSERT_NO_THROW (List<int> L2(2,6));
}
TEST(List, cant_create_with_negative_size)
{
    ASSERT_ANY_THROW(List<int> L1(-1));
}

TEST(List, can_get_size)
{
    List<int> L1(1);
    ASSERT_EQ(1, L1.size());
}
TEST(List, cant_found_element_with_negative_index)
{
    List<int> L1(5, 6);
    ASSERT_ANY_THROW(L1[-7]);
}
TEST(List, cant_found_element_with_too_large_index)
{
    List<int> L1(5, 6);
    ASSERT_ANY_THROW(L1[10]);
}
TEST(List, can_insert_element)
{
    List<int> L1(3, 6);
    List<int> L_exp(4, 6);
    //std::cout<<L1<< std:: endl;
    L1[2]=3;
    //std::cout<<L1<< std:: endl;
    L_exp[2]=3;
    //std::cout<<L_exp<< std:: endl;

    List<int>::Node* curr = L1.get_first();
    for (int i = 0; i < 2; i++)
        curr = curr->next;

    L1.insert(6, curr);
   // std::cout<<L1<< std:: endl;


    ASSERT_EQ(L1, L_exp);

}

TEST(List, can_isert_first_element)
{
    List<int> L1(5, 6);
    List<int> L_exp(6, 6);

    //std::cout<<L1<< std:: endl;
    //std::cout<<L_exp<< std:: endl;


    L1[2]=7;
    //std::cout<<L1<< std:: endl;

    L_exp[3]=7;
    //std::cout<<L_exp<< std:: endl;

    L1.insert_front(6);
    //std::cout<<L1<< std:: endl;
    ASSERT_EQ(L1, L_exp);

}
TEST(List, can_erase_element)
{
    List<int> L1(4, 5);
    List<int> L_exp(3, 5);

    //L1 = 5 5 5 5
    L1[3] = 2;
    //L1 = 5 5 2 5
    //L2 = 5 5 5
    //std::cout<<L1<< std:: endl;
    //std::cout<<L_exp<< std:: endl;

    List<int>::Node* curr = L1.get_first();
    for (int i = 0; i < 2; i++)
        curr = curr->next;

    L1.erase(curr);
    //std::cout<<L1<< std:: endl;

    ASSERT_EQ(L1, L_exp);
}



TEST(List, can_erase_first_element)
{
    List<int> L1(4, 5);
    List<int> L_exp(3, 5);
    L1[0] = 1;
    //L1 = 1 5 5 5
    //L2 = 5 5 5

    L1.erase_front();
    ASSERT_EQ(L1, L_exp);
}
TEST(List, can_find_element)
{
    List<int> L1(5, 6);
    ASSERT_NO_THROW(L1.find(6));
}
TEST(List, cant_find_element_not_in_list)
{
    List<int> L1(5, 6);
    ASSERT_EQ(L1.find(12), nullptr);
}
TEST(List, can_get_first)
{
    List<int> L1(5, 6);
    ASSERT_EQ(L1.get_first()->data, 6);
}

TEST(List, can_insert_in_end) {
    List<int> L1(4, 5);
   // std::cout<<L1<< std:: endl;
    List<int> L_exp(5, 5);
    //std::cout<<L_exp<< std:: endl;
    L1[3] = 1;
   // std::cout<<L1<< std:: endl;
    L_exp[3] = 1;
    //std::cout<<L_exp<< std:: endl;
    L1.insert_end (5);
    //std::cout<<L1<< std:: endl;
    ASSERT_EQ(L1, L_exp);
}
TEST(List, can_isert_first_element_empty_list)
{
    List<int> L1;
    List<int> L_exp(1, 5);
    L1.insert_front(5);
    //std::cout<<L1<< std:: endl;
    ASSERT_EQ(L1, L_exp);

}
TEST(List, cant_erase_first_element_empty_list)
{
    List<int> L1;
    ASSERT_ANY_THROW(L1.erase_front());
}
TEST(List, can_erase_end) {
List<int> L1(5, 5);
//std::cout<<L1<< std:: endl;
List<int> L_exp(4, 5);
//std::cout<<L_exp<< std:: endl;
L1[3] = 1;
//std::cout<<L1<< std:: endl;
L_exp[3] = 1;
//std::cout<<L_exp<< std:: endl;
L1.erase_end();
//std::cout<<L1<< std:: endl;
ASSERT_EQ(L1, L_exp);
}

TEST(List, can_erase_last_selected) {
    List <int> L1(6,2);
    L1[1] = 5;
    L1[2] = 3;
    L1[5] = 5;
    //std::cout<<"L1: "<<L1<< std:: endl;
    List <int> L_exp(5,2);
    L_exp[1] = 5;
    L_exp[2] = 3;
    L_exp[4] = 5;
    //std::cout<<"L_exp: "<< L_exp << std:: endl;
    L1.erase_last_selected(2);
    //std::cout<<"L1 after: "<< L1 << std:: endl;
    ASSERT_EQ(L1, L_exp);
    // L1 - 245667, L_exp - 24567,

}

TEST(List, cant_erase_nonequal_one_element_) {
    List <int> L1(1,2);
    List <int> L_exp(1,2);
    L1.erase_last_selected(3);
    ASSERT_EQ(L1, L_exp);
}

TEST (List, cant_erase_in_empty_list) {
    List <int> L1;//(0);
    ASSERT_ANY_THROW(L1.erase_last_selected(2));
}
TEST(List, can_erase_equal_one_element_) {
    List <int> L1(1,2);
    List <int> L_exp;
    L1.erase_last_selected(2);
    ASSERT_EQ(L_exp, L1);
}

TEST(List, cant_erase_no_exist) {
List <int> L1(6,2);
L1[1] = 4;
L1[2] = 5;
L1[3] = 5;
L1[4] = 9;
L1[5] = 8;
//std::cout<<"L1: "<<L1<< std:: endl;
List <int> L_exp = L1;
//std::cout<<"L_exp: "<< L_exp << std:: endl;
L1.erase_last_selected(7);
//std::cout<<"L1 after: "<< L1 << std:: endl;
ASSERT_EQ(L1, L_exp);
// L1 - 245667, L_exp - 24567,
}

//Teсты итератор

TEST(List, can_begin_iterator) {
    List<int> L1;
    //auto it = L1.begin();
    ASSERT_NO_THROW(auto it = L1.begin(););
}
TEST(List, can_end_iterator) {
    List<int> L1;
    ASSERT_NO_THROW(auto it = L1.end(););
}

TEST(List, can_step_forvard) {
    List<int> L1(2, 7);
    L1[1] = 3;
    auto it = L1.begin();
    it++;
    ASSERT_EQ(L1[1], *it);
}
TEST(List, cant_step_out_of_range) {
    List<int> L1(2, 7);
    L1[1] = 3;
    auto it = L1.begin();
    it++;
    ASSERT_ANY_THROW(it++);
}

TEST(List, can_get_reference) {
    List<int> L1(2, 7);
    L1[1] = 3;
    auto it = L1.begin();
    it++;
    ASSERT_EQ(&(L1[1]), it.operator->());
}

TEST(List, can_compare_equal_iterators) {
    List<int> L1(2, 7);
    L1[1] = 3;
    auto it1 = L1.begin();
    it1++;
    auto it2 = L1.begin();
    it2++;
    ASSERT_EQ(it1, it2);
}
TEST(List, can_compare_not_equal_iterators) {
    List<int> L1(2, 7);
    L1[1] = 3;
    auto it1 = L1.begin();
    it1++;
    auto it2 = L1.begin();
    ASSERT_NE(it1, it2);
}