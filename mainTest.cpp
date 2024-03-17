//
// Created by raz29 on 12/03/2024.
//
#include "olympics24a2.h"
#include <string>
#include <iostream>
#include "HashTable.h"
#include <cassert>
#include "olympics24a2.h"

void Test_hash(){
    auto hash_f = [](int team_id , int num){
        return (team_id)%num;
    };
    HashTable<int,Team> map(hash_f);
    int size = 1000;
    Team* team_array[size];
    for (int i = 0; i < size; ++i) {
        team_array[i] = new Team(i);
        assert(map.insert(team_array[i]->get_id_ref() , team_array[i]) == StatusType::SUCCESS);
        assert(map.insert(team_array[i]->get_id_ref() , team_array[i]) == StatusType::FAILURE);
        assert(map.search(team_array[i]->get_id_ref()));
    }
    assert(map.get_size() == 1000);
    for (int i = 0; i < size; ++i) {
        //map.remove(team_array[i]->get_id_ref() , team_array[i]);
        assert(map.remove(team_array[i]->get_id_ref()) == StatusType::SUCCESS);
    }
    assert(map.get_size() == 0);
    for (int i = 0; i < size; ++i) {
       delete team_array[i];
    }

}

void Test_Team(){
    Team team(10);
    Team team2(5);

    int size = 100;
    for (int i = 1; i < size+1; ++i) {
        team.add_player(i%50);
    }
    assert(team.get_size() == 98);
    for (int i = 1; i < size+1; ++i) {
        team.remove_newest_player();
    }
    assert(team.get_size() == 0);


    team.add_player(1);
    team.add_player(2);
    team.add_player(3);
    assert(team.get_size() == 3);
    team.remove_newest_player();
    assert(team.get_size() == 2);
    team.remove_newest_player();
    team.remove_newest_player();
    team.remove_newest_player();
    team.remove_newest_player();
    assert(team.get_size() == 0);

    team.add_player(1);
    team.add_player(2);
    team.add_player(3);

    team2.add_player(1);

    team.play_match(&team2);

    assert(team.get_number_of_wins() == 1);
    assert(team2.get_number_of_wins() == 0);
    team.play_match(&team2);
    team.play_match(&team2);
    team.play_match(&team2);
    assert(team2.get_number_of_wins() == 0);
    assert(team.get_number_of_wins() == 4);
    team2.add_player(2);
    team2.add_player(3);
    team.play_match(&team2);
    team2.play_match(&team);
    assert(team.getStrength() == team2.getStrength());
    assert(team.get_number_of_wins() == 4);
    assert(team2.get_number_of_wins() == 2);
    team.add_player(10);
    team.add_player(10);
    team.play_match(&team2);
    team2.play_match(&team);
    assert(team.get_number_of_wins() == 6);
    assert(team2.get_number_of_wins() == 2);
}
void simp_aux(AvlTree<int , Player*>& b){
    auto arr = b.get_tree_as_array();
    delete arr[0];
    delete[] arr;
}
void simp(){
    Player* a = new Player(20,12);
    AvlTree<int , Player*> tree;
    tree.insert(12 ,a );
   simp_aux(tree);
    assert(a->getPlayerStrength() == 12);
   delete a;
}

void Test_union_team(){
    Team team1(10);
    Team team2(20);
    Team team3(30);

    for (int i = 1; i < 10; ++i) {
        team1.add_player(i);
    }
    for (int i = 20; i < 30; ++i) {
        team3.add_player(i);
    }
    for (int i = 10; i < 20; ++i) {
        team2.add_player(i);
    }


    team1.merge_team_into_me(&team2);
    assert(team1.get_median_strength() == 10);
    assert(team1.get_size() == 19);
    team1.merge_team_into_me(&team3);
    assert(team1.get_size() == 29);
    assert(team2.get_size() == team3.get_size() && team3.get_size() == 0);
    Team team4(40);
    team1.merge_team_into_me(&team4); // empty team into full team
    assert(team1.get_size() == 29);
    assert(team1.get_median_strength() ==15);

    Team team5(50);
    team5.merge_team_into_me(&team1); // full team into null
    assert(team5.get_size() == 29);
    assert(team5.get_median_strength() ==15);

}

void Test_Median(){
    Team team1(10);
    team1.add_player(1);
    assert(team1.get_median_strength() == 1);
    team1.add_player(3);
    team1.add_player(3);
    team1.add_player(7);
    team1.add_player(8);
    team1.add_player(5);
    assert(team1.get_median_strength() == 5);
    assert(team1.getStrength() == 30);
    team1.remove_newest_player();
    assert(team1.get_median_strength() == 3);
    assert(team1.getStrength() == 15);
    Team team2(20);
    team2.add_player(2);
    team2.add_player(3);
    team2.add_player(4);
    team2.add_player(6);
    team2.add_player(6);
    assert(team2.get_median_strength() == 4);
    assert(team2.getStrength() == 20);

}

//void test_oly_creation(){
//    olympics_t olympicsObj;
//    olympicsObj.add_team(10);
//    olympicsObj.add_team(10);
//
//}
//void olympic_test(){
//    test_oly_creation();
//}
void test_destroyer(){//check with valgrind
    auto hash_f = [](int team_id , int num){
        return (team_id)%num;
    };
    int a = 10;
    int b = 20;
    int c = 30;
    HashTable<int , Team>* hashTable = new HashTable<int ,Team>(hash_f);
    Team* team = new Team(a);
    Team* team2 = new Team(b);
    Team* team3 = new Team(c);
    hashTable->insert(team->get_id_ref(),team);
    hashTable->insert(team2->get_id_ref(),team2);
    hashTable->insert(team3->get_id_ref(),team3);
    hashTable->search(a)->add_player(1);
    hashTable->search(a)->add_player(2);
    delete hashTable;
}
void test_oly_inti(){
    olympics_t* olympics = new olympics_t();
    int a = 10;
    int b = 20;
    int c = 30;
    olympics->add_team(a);
    olympics->add_team(b);
    olympics->add_team(c);
    int size = 10;
    for (int i = 0; i < size ; ++i) {
        olympics->add_player(a,i);
    }
    olympics->remove_newest_player(a);
    delete olympics;

}

void test_turni(){
    olympics_t* olympics = new olympics_t();

    olympics->add_team(1);
    olympics->add_team(3);
    olympics->add_team(4);
    olympics->add_team(5);
    olympics->add_team(6);
    olympics->add_team(60);
    olympics->add_team(7);
    olympics->add_team(8);
    olympics->add_team(9);
    olympics->add_team(10);
    olympics->add_team(13);

    olympics->add_player(1,1);
    olympics->add_player(3,3);
    olympics->add_player(4,4);
    olympics->add_player(5,5);
    olympics->add_player(6,6);
    olympics->add_player(60,6);
    olympics->add_player(7,7);
    olympics->add_player(8,8);
    olympics->add_player(9,9);
    olympics->add_player(10,10);
    olympics->add_player(13,13);

    assert(olympics->play_tournament(0 ,11).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(0 ,0).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(1 ,0).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(11 ,4).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(4 ,4).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(-1 ,4).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(-1 ,-4).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(1 ,-4).status() == StatusType::INVALID_INPUT);
    assert(olympics->play_tournament(1 ,5).status() == StatusType::FAILURE);// !(2^i)
    assert(olympics->play_tournament(1 ,13).status() == StatusType::FAILURE);// !(2^i)
    assert(olympics->play_tournament(4 ,13).status() == StatusType::FAILURE);// !(2^i)
    assert(olympics->play_tournament(3 ,11).status() == StatusType::FAILURE);// !(2^i)

    assert(olympics->play_tournament(4 ,11).ans() == 10);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 0);
    assert(olympics->num_wins_for_team(6).ans() == 0);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 1);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 2);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 0);

    assert(olympics->play_match(1 , 7).ans() == 7);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 0);
    assert(olympics->num_wins_for_team(6).ans() == 0);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 2);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 2);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 0);

    assert(olympics->play_match(7 , 13).ans() == 13);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 0);
    assert(olympics->num_wins_for_team(6).ans() == 0);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 2);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 2);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    assert(olympics->play_match(6 , 60).ans() == 6);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 0);
    assert(olympics->num_wins_for_team(6).ans() == 1);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 2);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 2);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    assert(olympics->play_tournament(3 ,9).ans() == 9);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 0);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 3);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    assert(olympics->play_tournament(4 ,5).ans() == 5);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 1);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 3);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    assert(olympics->play_tournament(1 ,5).ans() == 5);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 3);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    olympics->play_match(9,10);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 3);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 4);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    olympics->remove_team(8);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).status() == StatusType::FAILURE);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    olympics->add_team(8);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 0);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);

    olympics->add_team(14);
    olympics->add_team(15);
    olympics->add_team(16);
    olympics->add_team(40);
    olympics->add_team(10);

    olympics->add_player(14,14);
    olympics->add_player(15,15);
    olympics->add_player(16,16);
    olympics->add_player(40,4);
    olympics->add_player(10,1);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(10).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(40).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 3);
    assert(olympics->num_wins_for_team(8).ans() == 0);
    assert(olympics->num_wins_for_team(9).ans() == 5);
    assert(olympics->num_wins_for_team(10).ans() == 3);
    assert(olympics->num_wins_for_team(13).ans() == 1);
    assert(olympics->num_wins_for_team(14).ans() == 0);
    assert(olympics->num_wins_for_team(15).ans() == 0);
    assert(olympics->num_wins_for_team(16).ans() == 0);

    assert(olympics->play_tournament(1,16).ans() == 16);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(10).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 1);
    assert(olympics->num_wins_for_team(40).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 3);
    assert(olympics->num_wins_for_team(6).ans() == 2);
    assert(olympics->num_wins_for_team(60).ans() == 0);
    assert(olympics->num_wins_for_team(7).ans() == 4);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 6);
    assert(olympics->num_wins_for_team(10).ans() == 4);
    assert(olympics->num_wins_for_team(13).ans() == 3);
    assert(olympics->num_wins_for_team(14).ans() == 2);
    assert(olympics->num_wins_for_team(15).ans() == 3);
    assert(olympics->num_wins_for_team(16).ans() == 4);

    assert(olympics->play_tournament(1,6).ans() == 6);

    assert(olympics->num_wins_for_team(1).ans() == 0);
    assert(olympics->num_wins_for_team(10).ans() == 0);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->num_wins_for_team(4).ans() == 2);
    assert(olympics->num_wins_for_team(40).ans() == 0);
    assert(olympics->num_wins_for_team(5).ans() == 4);
    assert(olympics->num_wins_for_team(6).ans() == 5);
    assert(olympics->num_wins_for_team(60).ans() == 2);
    assert(olympics->num_wins_for_team(7).ans() == 4);
    assert(olympics->num_wins_for_team(8).ans() == 1);
    assert(olympics->num_wins_for_team(9).ans() == 6);
    assert(olympics->num_wins_for_team(10).ans() == 4);
    assert(olympics->num_wins_for_team(13).ans() == 3);
    assert(olympics->num_wins_for_team(14).ans() == 2);
    assert(olympics->num_wins_for_team(15).ans() == 3);
    assert(olympics->num_wins_for_team(16).ans() == 4);


    delete olympics;
}
void test_union_teams(){
    olympics_t* olympics = new olympics_t();

    assert(olympics->get_highest_ranked_team().ans() == -1);

    olympics->add_team(1);
    olympics->add_team(2);
    olympics->add_team(3);
    olympics->add_team(10);
    olympics->add_team(20);
    olympics->add_team(30);
    olympics->add_team(40);
    olympics->add_team(50);

    assert(olympics->get_highest_ranked_team().ans() == 0);
    assert(olympics->unite_teams(1,2)== StatusType::SUCCESS);// {} U {}
    assert(olympics->get_highest_ranked_team().ans() == 0);

    olympics->add_player(10 , 1);
    olympics->add_player(20 , 2);
    olympics->add_player(30 , 3);
    olympics->add_player(40 , 4);
    olympics->add_player(50 , 5);

    assert(olympics->get_highest_ranked_team().ans() == 5);

    assert(olympics->num_wins_for_team(40).ans() == 0);
    assert(olympics->play_match(10 , 40).ans() == 40);
    assert(olympics->num_wins_for_team(40).ans() == 1);

    assert(olympics->unite_teams(10 , 5) == StatusType::FAILURE);
    assert(olympics->unite_teams(5 , 10) == StatusType::FAILURE);
    assert(olympics->unite_teams(10 , 50) == StatusType::SUCCESS);

    assert(olympics->get_highest_ranked_team().ans() == 10); //team 10

    assert(olympics->num_wins_for_team(10).ans() == 0);
    assert(olympics->play_match(10 , 40).ans() == 10);
    assert(olympics->num_wins_for_team(10).ans() == 1);
    assert(olympics->num_wins_for_team(50).status() == StatusType::FAILURE);

    assert(olympics->get_highest_ranked_team().ans() == 11); //team 10 | 1,5  - w:1
    assert(olympics->unite_teams(10,1) == StatusType::SUCCESS);//team1 U {}
    assert(olympics->get_highest_ranked_team().ans() == 11); //team 10 | 1,5  - w:1

    assert(olympics->unite_teams(10 , 40) == StatusType::SUCCESS);
    assert(olympics->num_wins_for_team(10).ans() == 1);
    assert(olympics->num_wins_for_team(40).status() == StatusType::FAILURE);

    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1

    assert(olympics->remove_team(30) == StatusType::SUCCESS);
    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1
    assert(olympics->remove_team(30) == StatusType::FAILURE);
    assert(olympics->get_highest_ranked_team().ans() == 13); // team 10 | 1,4,5 - w:1

    assert(olympics->unite_teams(3,1) == StatusType::SUCCESS);//{} U team1
    assert(olympics->num_wins_for_team(10).status() == StatusType::FAILURE);
    assert(olympics->num_wins_for_team(3).ans() == 0);
    assert(olympics->get_highest_ranked_team().ans() == 12); // team 3 | 1,4,5 - w:0

    delete olympics;
}

void test_init_o(){
    olympics_t* olympics = new olympics_t();
    assert(olympics->add_team(10) == StatusType::SUCCESS);
    assert(olympics->add_team(10) == StatusType::FAILURE);
    assert(olympics->add_team(0) == StatusType::INVALID_INPUT);
    assert(olympics->add_team(-1) == StatusType::INVALID_INPUT);
    assert(olympics->add_team(20) == StatusType::SUCCESS);

    assert(olympics->add_player(10 , 1) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 3) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 4) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 5) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 6) == StatusType::SUCCESS);
    assert( olympics->add_player(10 , 7) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 8) == StatusType::SUCCESS);
   assert( olympics->add_player(10 , 9) == StatusType::SUCCESS);
    assert( olympics->add_player(10 , 10) == StatusType::SUCCESS);
    assert( olympics->add_player(10 , 13) == StatusType::SUCCESS);

    assert(olympics->add_player(0 , 1) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(-1 , 1) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(1 , -1) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(0 , -1) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(-1 , -1) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(-1 , 0) == StatusType::INVALID_INPUT);
    assert(olympics->add_player(1 , 0) == StatusType::INVALID_INPUT);

    assert(olympics->play_match(10 ,20).status() == StatusType::FAILURE);
    assert(olympics->play_match(10 ,5).status() == StatusType::FAILURE);
    assert(olympics->play_match(5 ,10).status() == StatusType::FAILURE);
    assert(olympics->play_match(20 ,10).status() == StatusType::FAILURE);


    assert(olympics->add_player(20 , 3) == StatusType::SUCCESS);
    assert(olympics->num_wins_for_team(20).ans() == 0);
    assert(olympics->play_match(10,20).ans() == 10);
    assert(olympics->num_wins_for_team(20).ans() == 1);
    assert(olympics->play_match(20,10).ans() == 10);
    assert(olympics->num_wins_for_team(20).ans() == 2);

    assert(olympics->remove_team(20) == StatusType::SUCCESS);
    assert(olympics->add_player(20 , 3) == StatusType::FAILURE);

    delete olympics;

}

void olympics_tests(){
    test_union_teams();
    test_init_o();
    test_turni();

}

int main(){
    simp();
    Test_hash();
    Test_Team();
    Test_union_team();
    Test_Median();
    test_destroyer();
    test_oly_inti();
   // olympic_test();
}