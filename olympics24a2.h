// 
// 234218 Data Structures 1.
// Semester: 2024A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef OLYMPICSA2_H_
#define OLYMPICSA2_H_

#include "wet2util.h"
#include "HashTable.h"
#include "Team.h"

static auto hash_func = [](int team_id , int table_size){
    return (team_id)%table_size;
};

class olympics_t {
private:
	//
	// Here you may add anything you want
	// im the number one ranger this side of the mississippi
    int m_number_of_teams;
    HashTable<int , Team>* m_table;
    AvlTree<int, int>* m_team_tree;

    //strength , id


    void update_team_strength_in_tree(TreeNode<int ,int >* teamNode);
    StatusType remove_teamAux(int teamId, int teamStrength = -1);


public:
	// <DO-NOT-MODIFY> {
    olympics_t();

	virtual ~olympics_t();

    StatusType add_team(int teamId);

    StatusType remove_team(int teamId);

    StatusType add_player(int teamId, int playerStrength);

    StatusType remove_newest_player(int teamId);

    output_t<int> play_match(int teamId1, int teamId2);

    output_t<int> num_wins_for_team(int teamId);

    output_t<int> get_highest_ranked_team();

    StatusType unite_teams(int teamId1, int teamId2);

    output_t<int> play_tournament(int lowPower, int highPower);
	
	// } </DO-NOT-MODIFY>
};

#endif // OLYMPICSA2_H_
