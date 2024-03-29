////
//// Created by raz29 on 12/03/2024.
////
//#include "olympics24a2.h"
//#include <string>
//#include <iostream>
//#include "HashTable.h"
//#include <cassert>
//#include "olympics24a2.h"
//
//
//
//void TestRankTree()
//{
//    AvlTree<int, int> tree = AvlTree<int, int>();
//    for (int i = 1; i < 10; i++)
//    {
//        tree.insert(i, i);
//    }
//    assert(tree.getNodeIndex(tree.find(7)) == 7);
//    for (int i = 1; i < 10; i++)
//    {
//        tree.insert(i, i + 1, true);
//    }
//    tree.printBinaryTree(5);
//    tree.remove(4, 4);
//    tree.remove(4, 5);
//    tree.remove(5, 5);
//    tree.remove(5, 6);
//    tree.printBinaryTree(5);
//    assert(tree.getNodeIndex(tree.find(9, 9)) == 14);
//    assert(tree.getNodeByIndex(14) == tree.find(9, 9));
//    assert(tree.getNodeByIndex(4) == tree.find(2, 2));
//
//    AvlTree<int, int> tree2 = AvlTree<int, int>();
//    for (int i = 1; i <= 1000; i++)
//    {
//        tree2.insert(i, i);
//    }
//    assert(tree2.getNodeIndex(tree2.find(7)) == 7);
//    assert(tree2.getNodeIndex(tree2.find(456, 456)) == 456);
//    int a = tree2.getNodeIndex(tree2.find(999));
//    for (int i = 1; i <= 20; i++)
//    {
//        tree2.remove(50 * i);
//    }
//    int b = tree2.getNodeIndex(tree2.find(999));
//    assert(tree2.getNodeIndex(tree2.find(999)) == 980);
//
//    printf("Rank tree test passed\n");
//}
//
//void TestOtherTree()
//{
//    AvlTree<int, int> tree = AvlTree<int, int>();
//    //tree.insert(0, 1, 5);
//    //tree.insert(1, 1, 5);
//    //tree.insert(2, 2, 10);
//    //tree.setValueToNodes(tree.find(1), nullptr, 7);
//    //tree.setValueToNodes(tree.find(0), nullptr, 5);
//    //tree.setValueToNodes(tree.find(2), tree.find(1), 4);
//
//    //tree.remove(1);
//
//
//
//    for (int i = 1; i <= 14; i++)
//    {
//        tree.insert(i, i);
//    }
//    for (int i = 1; i <= 4; i++)
//    {
//        tree.insert(i, i + 1);
//    }
//    assert(tree.getSize() == 18);
//    tree.setValueToNodes(tree.findMostLeft(4), tree.find(12), 5);
//    tree.setValueToNodes(tree.find(5), tree.find(13), 10);
//    int as = tree.getNodeCalculatedNumOfWins(tree.find(7));
//    assert(tree.getNodeCalculatedNumOfWins(tree.find(7)) == 15);
//    assert(tree.getNodeCalculatedNumOfWins(tree.find(13)) == 10);
//    assert(tree.getNodeCalculatedNumOfWins(tree.find(14)) == 0);
//    tree.printBinaryTree(5);
//    assert(tree.getNodeCalculatedNumOfWins(tree.findMostLeft(4)) == 0);
//    assert(tree.getNodeCalculatedNumOfWins(tree.findMostRight(4)) == 5);
//    assert(tree.getNodeCalculatedNumOfWins(tree.find(3)) == 0);
//
//
//    for (int i = 1; i <= 4; i++)
//    {
//        tree.insert(4, 4, true);
//    }
//    tree.insert(5, 6, true);
//    tree.printBinaryTree(5);
//    printf("Other tree test passed\n");
//}
//void Test_hash() {
//    auto hash_f = [](int team_id, int num) {
//        return (team_id) % num;
//    };
//    HashTable<int, Team> map(hash_f);
//    int size = 1000;
//    Team* team_array[1000];
//    for (int i = 0; i < size; ++i) {
//        team_array[i] = new Team(i);
//        assert(map.insert(team_array[i]->get_id_ref(), team_array[i]) == StatusType::SUCCESS);
//        assert(map.insert(team_array[i]->get_id_ref(), team_array[i]) == StatusType::FAILURE);
//        assert(map.search(team_array[i]->get_id_ref()));
//    }
//    assert(map.get_size() == 1000);
//    for (int i = 0; i < size; ++i) {
//        //map.remove(team_array[i]->get_id_ref() , team_array[i]);
//        assert(map.remove(team_array[i]->get_id_ref()) == StatusType::SUCCESS);
//    }
//    assert(map.get_size() == 0);
//    for (int i = 0; i < size; ++i) {
//        delete team_array[i];
//    }
//
//}
//
//void Test_Team() {
//    Team team(10);
//    Team team2(5);
//
//    int size = 100;
//    for (int i = 1; i < size + 1; ++i) {
//        team.add_player(i % 50);
//    }
//    assert(team.get_size() == 98);
//    for (int i = 1; i < size + 1; ++i) {
//        team.remove_newest_player();
//    }
//    assert(team.get_size() == 0);
//
//
//    team.add_player(1);
//    team.add_player(2);
//    team.add_player(3);
//    assert(team.get_size() == 3);
//    team.remove_newest_player();
//    assert(team.get_size() == 2);
//    team.remove_newest_player();
//    team.remove_newest_player();
//    team.remove_newest_player();
//    team.remove_newest_player();
//    assert(team.get_size() == 0);
//
//    team.add_player(1);
//    team.add_player(2);
//    team.add_player(3);
//
//    team2.add_player(1);
//
//    team.play_match(&team2);
//
//    assert(team.get_number_of_wins() == 1);
//    assert(team2.get_number_of_wins() == 0);
//    team.play_match(&team2);
//    team.play_match(&team2);
//    team.play_match(&team2);
//    assert(team2.get_number_of_wins() == 0);
//    assert(team.get_number_of_wins() == 4);
//    team2.add_player(2);
//    team2.add_player(3);
//    team.play_match(&team2);
//    team2.play_match(&team);
//    assert(team.getStrength() == team2.getStrength());
//    assert(team.get_number_of_wins() == 4);
//    assert(team2.get_number_of_wins() == 2);
//    team.add_player(10);
//    team.add_player(10);
//    team.play_match(&team2);
//    team2.play_match(&team);
//    assert(team.get_number_of_wins() == 6);
//    assert(team2.get_number_of_wins() == 2);
//}
//void simp_aux(AvlTree<int, Player*>& b) {
//    auto arr = b.get_tree_as_array();
//    delete arr[0];
//    delete[] arr;
//}
//void simp() {
//    Player* a = new Player(20, 12);
//    AvlTree<int, Player*> tree;
//    tree.insert(12, a);
//    simp_aux(tree);
//    assert(a->getPlayerStrength() == 12);
//    delete a;
//}
//
//void Test_union_team() {
//    Team team1(10);
//    Team team2(20);
//    Team team3(30);
//
//    for (int i = 1; i < 10; ++i) {
//        team1.add_player(i);
//    }
//    for (int i = 20; i < 30; ++i) {
//        team3.add_player(i);
//    }
//    for (int i = 10; i < 20; ++i) {
//        team2.add_player(i);
//    }
//
//
//    team1.merge_team_into_me(&team2);
//    assert(team1.get_median_strength() == 10);
//    assert(team1.get_size() == 19);
//    team1.merge_team_into_me(&team3);
//    assert(team1.get_size() == 29);
//    assert(team2.get_size() == team3.get_size() && team3.get_size() == 0);
//    Team team4(40);
//    team1.merge_team_into_me(&team4); // empty team into full team
//    assert(team1.get_size() == 29);
//    assert(team1.get_median_strength() == 15);
//
//    Team team5(50);
//    team5.merge_team_into_me(&team1); // full team into null
//    assert(team5.get_size() == 29);
//    assert(team5.get_median_strength() == 15);
//
//}
//
//void Test_Median() {
//    Team team1(10);
//    team1.add_player(1);
//    assert(team1.get_median_strength() == 1);
//    team1.add_player(3);
//    team1.add_player(3);
//    team1.add_player(7);
//    team1.add_player(8);
//    team1.add_player(5);
//    assert(team1.get_median_strength() == 5);
//    assert(team1.getStrength() == 30);
//    team1.remove_newest_player();
//    assert(team1.get_median_strength() == 3);
//    assert(team1.getStrength() == 15);
//    Team team2(20);
//    team2.add_player(2);
//    team2.add_player(3);
//    team2.add_player(4);
//    team2.add_player(6);
//    team2.add_player(6);
//    assert(team2.get_median_strength() == 4);
//    assert(team2.getStrength() == 20);
//
//}
//
////void test_oly_creation(){
////    olympics_t olympicsObj;
////    olympicsObj.add_team(10);
////    olympicsObj.add_team(10);
////
////}
////void olympic_test(){
////    test_oly_creation();
////}
//void test_destroyer() {//check with valgrind
//    auto hash_f = [](int team_id, int num) {
//        return (team_id) % num;
//    };
//    int a = 10;
//    int b = 20;
//    int c = 30;
//    HashTable<int, Team>* hashTable = new HashTable<int, Team>(hash_f);
//    Team* team = new Team(a);
//    Team* team2 = new Team(b);
//    Team* team3 = new Team(c);
//    hashTable->insert(team->get_id_ref(), team);
//    hashTable->insert(team2->get_id_ref(), team2);
//    hashTable->insert(team3->get_id_ref(), team3);
//    hashTable->search(a)->add_player(1);
//    hashTable->search(a)->add_player(2);
//    delete hashTable;
//}
//void test_oly_inti() {
//    olympics_t* olympics = new olympics_t();
//    olympics->add_team(10);
//    olympics->add_team(20);
//    olympics->add_team(30);
//    int size = 10;
//    for (int i = 0; i < size; ++i) {
//        olympics->add_player(10, i);
//    }
//    olympics->remove_newest_player(10);
//    delete olympics;
//
//}
//
//void test_turni() {
//    olympics_t* olympics = new olympics_t();
//
//    olympics->add_team(1);
//    olympics->add_team(3);
//    olympics->add_team(4);
//    olympics->add_team(5);
//    olympics->add_team(6);
//    olympics->add_team(60);
//    olympics->add_team(7);
//    olympics->add_team(8);
//    olympics->add_team(9);
//    olympics->add_team(10);
//    olympics->add_team(13);
//
//    olympics->add_player(1, 1);
//    olympics->add_player(3, 3);
//    olympics->add_player(4, 4);
//    olympics->add_player(5, 5);
//    olympics->add_player(6, 6);
//    olympics->add_player(60, 6);
//    olympics->add_player(7, 7);
//    olympics->add_player(8, 8);
//    olympics->add_player(9, 9);
//    olympics->add_player(10, 10);
//    olympics->add_player(13, 13);
//
//    assert(olympics->play_tournament(0, 11).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(0, 0).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(1, 0).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(11, 4).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(4, 4).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(-1, 4).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(-1, -4).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(1, -4).status() == StatusType::INVALID_INPUT);
//    assert(olympics->play_tournament(1, 4).status() == StatusType::FAILURE);// !(2^i)
//    assert(olympics->play_tournament(1, 13).status() == StatusType::FAILURE);// !(2^i)
//    assert(olympics->play_tournament(4, 13).status() == StatusType::FAILURE);// !(2^i)
//    assert(olympics->play_tournament(3, 11).status() == StatusType::FAILURE);// !(2^i)
//    assert(olympics->play_tournament(2, 11).status() == StatusType::FAILURE);// !(2^i)
//
//    assert(olympics->play_tournament(4, 11).ans() == 10);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 0);
//    assert(olympics->num_wins_for_team(6).ans() == 0);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 1);
//
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 2);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 0);
//
//    assert(olympics->play_match(1, 7).ans() == 7);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 0);
//    assert(olympics->num_wins_for_team(6).ans() == 0);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 2);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 2);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 0);
//
//    assert(olympics->play_match(7, 13).ans() == 13);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 0);
//    assert(olympics->num_wins_for_team(6).ans() == 0);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 2);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 2);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    assert(olympics->play_match(6, 60).ans() == 6);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 0);
//    assert(olympics->num_wins_for_team(6).ans() == 1);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 2);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 2);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    assert(olympics->play_tournament(3, 9).ans() == 9);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 0);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 3);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    assert(olympics->play_tournament(4, 5).ans() == 5);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 1);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 3);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    assert(olympics->play_tournament(1, 5).ans() == 5);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 3);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 3);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    olympics->play_match(9, 10);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 3);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 4);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    olympics->remove_team(8);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 4);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    olympics->add_team(8);
//    olympics->add_player(8, 8);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 0);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 4);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//
//    olympics->add_team(14);
//    olympics->add_team(15);
//    olympics->add_team(16);
//    olympics->add_team(40);
//    olympics->add_team(100);
//
//    olympics->add_player(14, 14);
//    olympics->add_player(15, 15);
//    olympics->add_player(16, 16);
//    olympics->add_player(40, 4);
//    olympics->add_player(100, 1);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(100).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 3);
//    assert(olympics->num_wins_for_team(8).ans() == 0);
//    assert(olympics->num_wins_for_team(9).ans() == 5);
//    assert(olympics->num_wins_for_team(10).ans() == 4);
//    assert(olympics->num_wins_for_team(13).ans() == 1);
//    assert(olympics->num_wins_for_team(14).ans() == 0);
//    assert(olympics->num_wins_for_team(15).ans() == 0);
//    assert(olympics->num_wins_for_team(16).ans() == 0);
//
//    assert(olympics->play_tournament(1, 16).ans() == 16);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(100).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 1);
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 3);
//    assert(olympics->num_wins_for_team(6).ans() == 2);
//    assert(olympics->num_wins_for_team(60).ans() == 0);
//    assert(olympics->num_wins_for_team(7).ans() == 4);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 6);
//    assert(olympics->num_wins_for_team(10).ans() == 5);
//    assert(olympics->num_wins_for_team(13).ans() == 3);
//    assert(olympics->num_wins_for_team(14).ans() == 2);
//    assert(olympics->num_wins_for_team(15).ans() == 3);
//    assert(olympics->num_wins_for_team(16).ans() == 4);
//
//    assert(olympics->play_tournament(1, 6).ans() == 6);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(100).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 2);
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 4);
//    assert(olympics->num_wins_for_team(6).ans() == 5);
//    assert(olympics->num_wins_for_team(60).ans() == 2);
//    assert(olympics->num_wins_for_team(7).ans() == 4);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 6);
//    assert(olympics->num_wins_for_team(10).ans() == 5);
//    assert(olympics->num_wins_for_team(13).ans() == 3);
//    assert(olympics->num_wins_for_team(14).ans() == 2);
//    assert(olympics->num_wins_for_team(15).ans() == 3);
//    assert(olympics->num_wins_for_team(16).ans() == 4);
//
//
//    assert(olympics->remove_newest_player(6) == StatusType::SUCCESS);
//    assert(olympics->remove_newest_player(6) == StatusType::FAILURE);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(100).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 2);
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 4);
//    assert(olympics->num_wins_for_team(6).ans() == 5);
//    assert(olympics->num_wins_for_team(60).ans() == 2);
//    assert(olympics->num_wins_for_team(7).ans() == 4);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 6);
//    assert(olympics->num_wins_for_team(10).ans() == 5);
//    assert(olympics->num_wins_for_team(13).ans() == 3);
//    assert(olympics->num_wins_for_team(14).ans() == 2);
//    assert(olympics->num_wins_for_team(15).ans() == 3);
//    assert(olympics->num_wins_for_team(16).ans() == 4);
//
//    assert(olympics->remove_team(7) == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(1).ans() == 0);
//    assert(olympics->num_wins_for_team(100).ans() == 0);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->num_wins_for_team(4).ans() == 2);
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->num_wins_for_team(5).ans() == 4);
//    assert(olympics->num_wins_for_team(6).ans() == 5);
//    assert(olympics->num_wins_for_team(60).ans() == 2);
//    assert(olympics->num_wins_for_team(7).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(8).ans() == 1);
//    assert(olympics->num_wins_for_team(9).ans() == 6);
//    assert(olympics->num_wins_for_team(10).ans() == 5);
//    assert(olympics->num_wins_for_team(13).ans() == 3);
//    assert(olympics->num_wins_for_team(14).ans() == 2);
//    assert(olympics->num_wins_for_team(15).ans() == 3);
//    assert(olympics->num_wins_for_team(16).ans() == 4);
//
//    delete olympics;
//}
//void test_union_teams() {
//    olympics_t* olympics = new olympics_t();
//
//    assert(olympics->get_highest_ranked_team().ans() == -1);
//
//    olympics->add_team(1);
//    olympics->add_team(2);
//    olympics->add_team(3);
//    olympics->add_team(10);
//    olympics->add_team(20);
//    olympics->add_team(30);
//    olympics->add_team(40);
//    olympics->add_team(50);
//
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//    assert(olympics->unite_teams(1, 2) == StatusType::SUCCESS);// {} U {}
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//
//    olympics->add_player(10, 1);
//    olympics->add_player(20, 2);
//    olympics->add_player(30, 3);
//    olympics->add_player(40, 4);
//    olympics->add_player(50, 5);
//
//    assert(olympics->get_highest_ranked_team().ans() == 5);
//
//    assert(olympics->num_wins_for_team(40).ans() == 0);
//    assert(olympics->play_match(10, 40).ans() == 40);
//    assert(olympics->num_wins_for_team(40).ans() == 1);
//
//    assert(olympics->unite_teams(10, 5) == StatusType::FAILURE);
//    assert(olympics->unite_teams(5, 10) == StatusType::FAILURE);
//    assert(olympics->unite_teams(10, 50) == StatusType::SUCCESS);
//
//    assert(olympics->get_highest_ranked_team().ans() == 10); //team 10
//
//    assert(olympics->num_wins_for_team(10).ans() == 0);
//    assert(olympics->play_match(10, 40).ans() == 10);
//    assert(olympics->num_wins_for_team(10).ans() == 1);
//    assert(olympics->num_wins_for_team(50).status() == StatusType::FAILURE);
//
//    assert(olympics->get_highest_ranked_team().ans() == 11); //team 10 | 1,5  - w:1
//    assert(olympics->unite_teams(10, 1) == StatusType::SUCCESS);//team1 U {}
//    assert(olympics->get_highest_ranked_team().ans() == 11); //team 10 | 1,5  - w:1
//
//    assert(olympics->unite_teams(10, 40) == StatusType::SUCCESS);
//    assert(olympics->num_wins_for_team(10).ans() == 1);
//    assert(olympics->num_wins_for_team(40).status() == StatusType::FAILURE);
//
//    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1
//
//    assert(olympics->remove_team(30) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1
//    assert(olympics->remove_team(30) == StatusType::FAILURE);
//    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1
//
//    assert(olympics->unite_teams(3, 10) == StatusType::SUCCESS);//{} U team10
//    assert(olympics->num_wins_for_team(10).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(3).ans() == 0);
//    assert(olympics->get_highest_ranked_team().ans() == 12); // team 3 | 1,4,5 - w:0
//
//    delete olympics;
//}
//
//void test_init_o() {
//    olympics_t* olympics = new olympics_t();
//    assert(olympics->add_team(10) == StatusType::SUCCESS);
//    assert(olympics->add_team(10) == StatusType::FAILURE);
//    assert(olympics->add_team(0) == StatusType::INVALID_INPUT);
//    assert(olympics->add_team(-1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_team(20) == StatusType::SUCCESS);
//
//    assert(olympics->add_player(10, 1) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 3) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 4) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 5) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 6) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 7) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 8) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 9) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 10) == StatusType::SUCCESS);
//    assert(olympics->add_player(10, 13) == StatusType::SUCCESS);
//
//    assert(olympics->add_player(0, 1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(-1, 1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(1, -1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(0, -1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(-1, -1) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(-1, 0) == StatusType::INVALID_INPUT);
//    assert(olympics->add_player(1, 0) == StatusType::INVALID_INPUT);
//
//    assert(olympics->play_match(10, 20).status() == StatusType::FAILURE);
//    assert(olympics->play_match(10, 5).status() == StatusType::FAILURE);
//    assert(olympics->play_match(5, 10).status() == StatusType::FAILURE);
//    assert(olympics->play_match(20, 10).status() == StatusType::FAILURE);
//
//
//    assert(olympics->add_player(20, 3) == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(20).ans() == 0);
//    assert(olympics->num_wins_for_team(10).ans() == 0);
//    assert(olympics->play_match(10, 20).ans() == 10);
//    assert(olympics->num_wins_for_team(10).ans() == 1);
//    assert(olympics->play_match(20, 10).ans() == 10);
//    assert(olympics->num_wins_for_team(10).ans() == 2);
//
//    assert(olympics->remove_team(20) == StatusType::SUCCESS);
//    assert(olympics->add_player(20, 3) == StatusType::FAILURE);
//
//    delete olympics;
//
//}
//
//void test_ranked() {
//    olympics_t* olympics = new olympics_t();
//
//    assert(olympics->get_highest_ranked_team().ans() == -1);
//    olympics->add_team(10);
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//    olympics->add_team(20);
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//    olympics->add_team(30);
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//    olympics->add_team(40);
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//
//    olympics->add_player(10, 1); // 1 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 1);
//    olympics->add_player(20, 2);// 2 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 2);
//    olympics->add_player(10, 3); //1 ,3 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 6);
//    olympics->add_player(10, 5); //1 ,3,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 9);
//    olympics->add_player(10, 1); //1,1,3,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 12);
//    olympics->add_player(10, 1); //1,1,1,3,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 5);
//    olympics->add_player(40, 4); // 4 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 5);
//    olympics->add_player(30, 3); // 3 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 5);
//    olympics->add_player(40, 8); // 4,8 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 16);
//
//    assert(olympics->remove_team(40) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans() == 5);
//
//    assert(olympics->unite_teams(20, 30) == StatusType::SUCCESS);//2,3 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 6);
//
//    olympics->add_team(40);
//    assert(olympics->get_highest_ranked_team().ans() == 6);
//    olympics->add_player(40, 4); // 4 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 6);
//
//    assert(olympics->play_match(10, 40).ans() == 10);//1,1,1,3,5 w: 1 vs 4 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 6);
//    assert(olympics->play_match(10, 40).ans() == 10);//1,1,1,3,5 w: 2 vs 4 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 7);
//    assert(olympics->play_match(10, 40).ans() == 10);//1,1,1,3,5 w: 3 vs 4 w:0
//    assert(olympics->get_highest_ranked_team().ans() == 8);
//
//    assert(olympics->unite_teams(40, 10) == StatusType::SUCCESS);//1,1,1,3,4,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 18);
//
//    assert(olympics->remove_newest_player(40) == StatusType::SUCCESS); //1,1,3,4,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 15); // team 40
//
//    assert(olympics->remove_newest_player(40) == StatusType::SUCCESS); //1,3,4,5 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 16); // team 40
//
//
//    assert(olympics->remove_newest_player(40) == StatusType::SUCCESS); //1,3,4 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 9); // team 40
//
//    assert(olympics->remove_newest_player(40) == StatusType::SUCCESS); //1,4 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 8); // team 40
//
//    assert(olympics->remove_newest_player(40) == StatusType::SUCCESS); //4 w: 0
//    assert(olympics->get_highest_ranked_team().ans() == 6); // team 20
//
//
//    delete olympics;
//}
//
//
//void test_big(){
//    olympics_t* olympics = new olympics_t();
//
//    assert(olympics->get_highest_ranked_team().ans() == -1);
//
//    assert(olympics->add_team(100) == StatusType::SUCCESS);
//    assert(olympics->add_team(100) == StatusType::FAILURE);
//    assert(olympics->add_team(-100) == StatusType::INVALID_INPUT);
//    assert(olympics->add_team(-100) == StatusType::INVALID_INPUT);
//    assert(olympics->add_team(0) == StatusType::INVALID_INPUT);
//    assert(olympics->add_team(100) == StatusType::FAILURE);
//    assert(olympics->add_team(100) == StatusType::FAILURE);
//    assert(olympics->add_team(200) == StatusType::SUCCESS);
//    assert(olympics->add_team(300) == StatusType::SUCCESS);
//    assert(olympics->add_team(400) == StatusType::SUCCESS);
//    assert(olympics->add_team(500) == StatusType::SUCCESS);
//    for (int i = 501; i < 600 ; ++i) {
//        assert(olympics->add_team(i) == StatusType::SUCCESS);
//        assert(olympics->add_team(i) == StatusType::FAILURE);
//        assert(olympics->add_team(-i) == StatusType::INVALID_INPUT);
//    }
//    for (int i = 500; i < 600; ++i) {
//        assert(olympics->num_wins_for_team(i).ans() == 0);
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 0);
//    for (int i = 500; i < 600; ++i) {
//        for (int j = 500; j < 600 ; ++j) {
//            if (i == j) continue;
//            assert(olympics->play_match(i ,j).status() == StatusType::FAILURE);
//            assert(olympics->play_match(i+200 ,j).status() == StatusType::FAILURE);
//            assert(olympics->play_match(i+200 ,j+200).status() == StatusType::FAILURE);
//            assert(olympics->play_match(i ,j+200).status() == StatusType::FAILURE);
//            assert(olympics->play_match(i ,i).status() == StatusType::INVALID_INPUT);
//            assert(olympics->play_match(-i ,j).status() == StatusType::INVALID_INPUT);
//            assert(olympics->play_match(-i ,-j).status() == StatusType::INVALID_INPUT);
//            assert(olympics->play_match(i ,-j).status() == StatusType::INVALID_INPUT);
//        }
//    }
//    for (int i = 500; i < 600 ; ++i) {
//       assert( olympics->add_player(i , 2*i) == StatusType::SUCCESS );
//       assert( olympics->add_player(i , -2*i) == StatusType::INVALID_INPUT );
//       assert( olympics->add_player(-i , 2*i) == StatusType::INVALID_INPUT );
//       assert( olympics->add_player(0 , 2*i) == StatusType::INVALID_INPUT );
//       assert( olympics->add_player(0 , 0) == StatusType::INVALID_INPUT );
//       assert( olympics->add_player(i , 0) == StatusType::INVALID_INPUT );
//       assert( olympics->add_player(i*2 , i) == StatusType::FAILURE );
//       assert( olympics->add_player(i , 3*i) == StatusType::SUCCESS );
//       assert( olympics->add_player(i , 4*i) == StatusType::SUCCESS );
//       assert( olympics->add_player(i , i +50)== StatusType::SUCCESS );
//       assert( olympics->add_player(i , (int)pow(i ,2) +50)== StatusType::SUCCESS ); //  i+50 ,2i ,3i , 4i ,i^2 +50
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 599*3*5);
//
//    for (int i = 599; i >= 500; --i) {
//        assert(olympics->get_highest_ranked_team().ans() == i*3*5);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(-i) == StatusType::INVALID_INPUT);
//        assert(olympics->remove_newest_player(2*i) == StatusType::FAILURE);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(i) == StatusType::FAILURE);
//    }
//    for (int i = 500; i < 600 ; ++i) {
//        assert( olympics->add_player(i , 2*i) == StatusType::SUCCESS );
//        assert( olympics->add_player(i , -2*i) == StatusType::INVALID_INPUT );
//        assert( olympics->add_player(-i , 2*i) == StatusType::INVALID_INPUT );
//        assert( olympics->add_player(0 , 2*i) == StatusType::INVALID_INPUT );
//        assert( olympics->add_player(0 , 0) == StatusType::INVALID_INPUT );
//        assert( olympics->add_player(i , 0) == StatusType::INVALID_INPUT );
//        assert( olympics->add_player(i*2 , i) == StatusType::FAILURE );
//        assert( olympics->add_player(i , 4*i) == StatusType::SUCCESS );
//        assert( olympics->add_player(i , 3*i) == StatusType::SUCCESS );
//        assert( olympics->add_player(i , i +50)== StatusType::SUCCESS );
//        assert( olympics->add_player(i , (int)pow(i ,2) +50)== StatusType::SUCCESS ); //  i+50 ,2i ,3i , 4i ,i^2 +50
//    }
//    for (int i = 599; i >= 500; --i) {
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS); // i+50 , 2i, 3i , 4i
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS); //  2i, 3i , 4i
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 599*3*3);
//
//    for (int i = 500; i < 600; ++i) {
//        assert(olympics->unite_teams(100 , i) == StatusType::SUCCESS);
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    for (int i = 501; i < 5000 ; ++i) {
//        assert(olympics->add_team(i) == StatusType::SUCCESS);
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    assert(olympics->add_player(100 , 321) == StatusType::SUCCESS);
//    assert(olympics->remove_newest_player(100) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    for (int i = 501; i < 5000 ; ++i) {
//        assert(olympics->add_player(i , i) == StatusType::SUCCESS);
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->add_player(i , i) == StatusType::SUCCESS);
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    assert(olympics->add_player(100 , 321) == StatusType::SUCCESS);
//    assert(olympics->remove_newest_player(100) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    for (int i = 501; i < 3900 ; ++i) {
//        assert(olympics->remove_team(i) == StatusType::SUCCESS);
//        assert(olympics->remove_team(i) == StatusType::FAILURE);
//    }
//    assert(olympics->add_team(57) == StatusType::SUCCESS);
//
//    for (int i = 3901 ; i < 4999; i+=2) {
//        assert(olympics->unite_teams(i , i+1) == StatusType::SUCCESS);
//        assert(olympics->remove_team(i) == StatusType::SUCCESS);
//    }
//    assert(olympics->get_highest_ranked_team().ans() == 550*300*3);
//    delete olympics;
//
//}
//
//void test_all(){
//    olympics_t* olympics = new olympics_t();
//
//    assert(olympics->add_team(100) == StatusType::SUCCESS);
//    assert(olympics->add_team(200) == StatusType::SUCCESS);
//    assert(olympics->add_team(300) == StatusType::SUCCESS);
//    assert(olympics->add_team(400) == StatusType::SUCCESS);
//    assert(olympics->add_team(500) == StatusType::SUCCESS);
//    assert(olympics->add_team(600) == StatusType::SUCCESS);
//    assert(olympics->add_team(700) == StatusType::SUCCESS);
//    assert(olympics->add_team(800) == StatusType::SUCCESS);
//    assert(olympics->add_team(900) == StatusType::SUCCESS);
//
//    assert( olympics->add_player(100 , 40) == StatusType::SUCCESS );
//    assert( olympics->add_player(100 , 50) == StatusType::SUCCESS );
//    assert( olympics->add_player(100 , 10) == StatusType::SUCCESS );
//    assert( olympics->add_player(100 , 20) == StatusType::SUCCESS );
//
//    assert( olympics->add_player(200 , 10) == StatusType::SUCCESS );
//    assert( olympics->add_player(200 , 11) == StatusType::SUCCESS );
//    assert( olympics->add_player(200 , 40) == StatusType::SUCCESS );
//    assert( olympics->add_player(200 , 41) == StatusType::SUCCESS );
//    assert( olympics->add_player(200 , 42) == StatusType::SUCCESS );
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*5);
//
//    assert(olympics->play_match(100 , 200).ans() == 100); //same strength
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*5 + 1);
//
//    assert(olympics->add_player(200 , 12) == StatusType::SUCCESS);
//
//    assert(olympics->add_player(300 , 30) == StatusType::SUCCESS);
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*6); // team 200
//
//    assert(olympics->play_tournament(40 , 1000).ans() == 200); //team 100 vs team200
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*6 + 1); // team 200
//
//    assert(olympics->num_wins_for_team(100).ans() == 1);
//    assert(olympics->num_wins_for_team(200).ans() == 1);
//
//    assert(olympics->add_player(400 , 40) == StatusType::SUCCESS);
//
//    assert(olympics->unite_teams(500 , 400) == StatusType::SUCCESS);//team500 : 40
//    assert(olympics->unite_teams(500 , 400) == StatusType::FAILURE);
//
//    assert(olympics->play_tournament(20 , 1000).ans() == 200);
//    assert(olympics->num_wins_for_team(100).ans() == 2);
//    assert(olympics->num_wins_for_team(200).ans() == 3);
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*6 + 3); // team 200
//
//    assert(olympics->remove_newest_player(200) == StatusType::SUCCESS); //remove 12 now : 10,11,40,41,42
//    assert(olympics->remove_newest_player(200) == StatusType::SUCCESS); //remove 12 now : 10,11,40,41
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*5 + 2); // team 100
//
//    assert(olympics->play_match(100 , 300).ans() == 100);
//    assert(olympics->play_match(100 , 300).ans() == 100);
//    assert(olympics->play_match(100 , 300).ans() == 100);
//    assert(olympics->play_match(100 , 300).ans() == 100);
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*5 + 6); // team 100
//
//    assert(olympics->add_player(400 , 40) == StatusType::FAILURE);
//    assert(olympics->add_player(600 , 60) == StatusType::SUCCESS);
//    assert(olympics->add_player(600 , 10) == StatusType::SUCCESS);
//    assert(olympics->add_player(600 , 90) == StatusType::SUCCESS);
//
//    assert(olympics->unite_teams(700 , 100) == StatusType::SUCCESS);//40 30 10 20
//    assert(olympics->add_player(700 , 90) == StatusType::SUCCESS);
//    assert(olympics->add_player(700 , 10) == StatusType::SUCCESS);//40 30 10 20 90 10 med = 30 s = 180
//
//    assert(olympics->get_highest_ranked_team().ans() == 40*5); // team 700
//
//    assert(olympics->num_wins_for_team(700).ans() == 0);
//
//    assert(olympics->unite_teams(800 , 900) == StatusType::SUCCESS);
//
//    assert(olympics->add_player(800 , 80) == StatusType::FAILURE);
//    assert(olympics->add_player(800 , 79) == StatusType::FAILURE);
//
//    assert(olympics->play_tournament(1 , 1000).status() == StatusType::FAILURE);
//    assert(olympics->play_tournament(160 , 181).ans() == 200);//team 200 , 600 ,700 ,800
//
//    assert(olympics->num_wins_for_team(200).ans() == 3);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 0);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//
//    assert(olympics->play_match(300 , 500).ans() == 500);
//
//    assert(olympics->num_wins_for_team(300).ans() == 0);
//    assert(olympics->num_wins_for_team(500).ans() == 1);
//
//    assert(olympics->play_tournament(160 , 181).status() == StatusType::FAILURE);//team 200 , 600 ,700 ,800
//
//    assert(olympics->play_tournament(160 , 181).ans() == 200);//team 200 , 600 ,700 ,800
//
//    assert(olympics->play_tournament(29 , 179).status() == StatusType::SUCCESS);//team 200 , 300 ,500 ,800
//
//    assert(olympics->num_wins_for_team(200).ans() == 5);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 0);
//    assert(olympics->num_wins_for_team(500).ans() == 1);
//
//    assert(olympics->play_tournament(29 , 30).status() == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).ans() == 5);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 0);
//    assert(olympics->num_wins_for_team(500).ans() == 2);
//
//    assert(olympics->play_tournament(30 , 31).status() == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).ans() == 5);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 0);
//    assert(olympics->num_wins_for_team(500).ans() == 3);
//
//    assert(olympics->add_player(300 , 100) == StatusType::SUCCESS);
//
//    assert(olympics->play_match(300 , 500).ans() == 300);
//
//    assert(olympics->num_wins_for_team(200).ans() == 5);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).ans() == 3);
//
//    assert(olympics->unite_teams(300 ,500) == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).ans() == 5);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//
//    assert(olympics->add_team(900) == StatusType::SUCCESS);
//    assert(olympics->add_player(900 , 160) == StatusType::SUCCESS);
//
//    assert(olympics->play_tournament(120 , 160).status() == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).ans() == 2);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 1);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//
//    assert(olympics->get_highest_ranked_team().ans() == 180 + 2);//team 600
//
//    for (int i = 1000; i < 5000 ; ++i) {
//        assert(olympics->add_team(i) == StatusType::SUCCESS);
//    }
//
//    assert(olympics->num_wins_for_team(200).ans() == 2);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 1);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//
//    assert(olympics->get_highest_ranked_team().ans() == 180 + 2);//team 600
//
//    for (int i = 1000; i < 5000 ; ++i) {
//        assert(olympics->add_player(i,2*i) == StatusType::SUCCESS);
//    }
//    assert(olympics->num_wins_for_team(200).ans() == 2);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 1);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//    assert(olympics->get_highest_ranked_team().ans() == 4999);//team 4999
//
//    for (int i = 4999; i > 1000 ; ++i) {
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->get_highest_ranked_team().ans() == i);
//    }
//
//    assert(olympics->remove_newest_player(1000) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans()== 180 + 2);//team 600
//
//    for (int i = 1000; i < 5000 ; ++i) {
//        assert(olympics->add_player(i,2*i) == StatusType::SUCCESS);
//    }
//    for (int i = 1000; i < 4999 ; ++i) {
//        assert(olympics->play_match(i,i+1).ans() == i+1);
//        assert(olympics->play_tournament(i,i+1).ans() == i+1);
//    }
//    assert(olympics->num_wins_for_team(200).ans() == 2);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 1);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//    assert(olympics->get_highest_ranked_team().ans() == 4999 + 2);//team 4999
//
//    assert(olympics->play_tournament(120 , 160).status() == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).ans() == 4);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//
//    for (int i = 4999; i > 1000 ; ++i) {
//        assert(olympics->remove_newest_player(i) == StatusType::SUCCESS);
//        assert(olympics->get_highest_ranked_team().ans() == i);
//    }
//
//    assert(olympics->remove_newest_player(1000) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans()== 180 + 2);//team 600
//
//    assert(olympics->num_wins_for_team(200).ans() == 4);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//
//    for (int i = 1000; i < 5000 ; ++i) {
//        assert(olympics->remove_team(i) == StatusType::SUCCESS);
//    }
//
//    assert(olympics->add_team(1000) == StatusType::SUCCESS);
//    assert(olympics->add_team(2000) == StatusType::SUCCESS);
//    assert(olympics->add_team(3000) == StatusType::SUCCESS);
//
//    assert(olympics->unite_teams(1000 ,200) == StatusType::SUCCESS);
//    assert(olympics->unite_teams(1000 ,900) == StatusType::SUCCESS);
//    assert(olympics->unite_teams(2000 ,3000) == StatusType::SUCCESS);
//    assert(olympics->unite_teams(900 ,3000) == StatusType::SUCCESS);
//
//    assert(olympics->num_wins_for_team(200).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 2);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 0);
//
//    assert(olympics->get_highest_ranked_team().ans()== 200);//team 900
//    assert(olympics->remove_newest_player(900) == StatusType::SUCCESS);
//    assert(olympics->remove_newest_player(900) == StatusType::SUCCESS);
//    assert(olympics->remove_newest_player(900) == StatusType::SUCCESS);
//    assert(olympics->get_highest_ranked_team().ans()== 320);//team 900
//    assert(olympics->play_match(900,600).ans() == 900);
//    assert(olympics->get_highest_ranked_team().ans()== 320 + 1);//team 900
//    assert(olympics->play_match(700,600).ans() == 600);
//    assert(olympics->remove_newest_player(900) == StatusType::SUCCESS);
//
//    assert(olympics->get_highest_ranked_team().ans()== 180 + 3);//team 600
//
//    assert(olympics->num_wins_for_team(200).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(700).ans() == 1);
//    assert(olympics->num_wins_for_team(800).ans() == 2);
//    assert(olympics->num_wins_for_team(600).ans() == 3);
//    assert(olympics->num_wins_for_team(300).ans() == 1);
//    assert(olympics->num_wins_for_team(500).status() == StatusType::FAILURE);
//    assert(olympics->num_wins_for_team(900).ans() == 1);
//
//    delete olympics;
//}
//
//void olympics_tests() {
//    test_init_o();
//    test_union_teams();
//    test_turni();
//    test_ranked();
//    test_big();
//
//}
//
//void small_test() {
//    olympics_t* olympics = new olympics_t();
//    olympics->add_team(10);
//    olympics->add_team(20);
//    olympics->add_player(10, 1);
//    olympics->add_player(20, 2);
//    olympics->add_player(20, 3);
//    delete olympics;
//}
//void test_list_deletion(){
//    List<Player*>* list = new List<Player*>;
//    Player** arrPlayer = new Player*[100];
//    for (int i = 0; i < 100; ++i) {
//        arrPlayer[i] = new Player(i,i);
//        list->addNode(arrPlayer[i]);
//    }
//
//    List<Player*>* list2 = new List<Player*>;
//    Player** arrPlayer2 = new Player*[100];
//    for (int i = 0; i < 100; ++i) {
//        arrPlayer2[i] = new Player(i,i);
//        list2->addNode(arrPlayer2[i]);
//    }
//
//    list->connect_list(*list2);
//    list->Delete_list_and_Data();
//    delete list2;
//    delete list;
//    delete[] arrPlayer;
//    delete[] arrPlayer2;
//}
//void test_from_txt(){
//    olympics_t* olympics = new olympics_t();
//
//    olympics->add_team(39);
//    olympics->add_team(67);
//    olympics->add_team(183);
//    olympics->add_team(187);
//
//    olympics->add_player(39,4715);
//    olympics->add_player(39,644);
//    olympics->add_player(39,2671);
//    olympics->add_team(69);
//    olympics->add_player(39,7093);
//    olympics->add_player(69,7945);
//    olympics->add_player(39,4817);
//    olympics->add_player(69,3364);
//    olympics->add_player(69,4662);
//    olympics->add_player(39,1868);
//
//    olympics->unite_teams(67,39);
//    olympics->unite_teams(67,69);
//
//    olympics->unite_teams(183,187);
//    olympics->unite_teams(183,81);
//    olympics->unite_teams(183,67);
//
//    delete olympics;
//
//
//}
//
//int main1(){
//    test_from_txt();
//    simp();
//    Test_hash();
//    Test_Team();
//    Test_union_team();
//    Test_Median();
//    small_test();
//    test_destroyer();
//    test_oly_inti();
//    olympics_tests();
//    //TestRankTree();
//    //TestOtherTree();
//    return 0;
//}