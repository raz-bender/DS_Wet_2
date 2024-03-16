//
// Created by raz29 on 09/03/2024.
//

#ifndef WET24_TO_PUBLISH_TEAM_H
#define WET24_TO_PUBLISH_TEAM_H
#include "AvlTree.h"
#include "list.h"
#include "wet2util.h"
#include "Player.h"
typedef AvlTree<int ,Player*>::Key_Data_pair** Pair_Ptr_arr;

class Team {
    int m_id;
    int m_size;
    int m_num_of_wins;
    Player* m_median_player;
    List<Player*>* m_newest_player;
    //strength player
    AvlTree<int ,Player*>* m_players;

    void set_median();

    Pair_Ptr_arr merge_arrays_key_data_pair(Pair_Ptr_arr arr1 , int size1 ,Pair_Ptr_arr arr2 , int size2);
    AvlTree<int, Player*>* create_tree_from_array(Pair_Ptr_arr arr,int size);
    void aux_create_empty_tree(TreeNode<int, Player *>* root ,TreeNode<int, Player *>* parent , int& redundant, int height);
    void aux_insert_data_to_tree(TreeNode<int , Player*>* root ,Pair_Ptr_arr arr , int &i ,int height , int teamId = -1);

public:


    Team(int teamId);
    ~Team();

    int get_size() const;
    void set_size(int size);

    int &get_id_ref();
    int get_id()const;

    StatusType add_player(int playerStrength);
    StatusType remove_newest_player();

    int getStrength() const;
    bool play_match(Team* team2);

    AvlTree<int, Player *>::Key_Data_pair** get_team_player_array();

    void merge_team_into_me(Team* team2);

    void add_point();
    int get_number_of_wins()const;

    void set_points(int points);

    //for testing
    int get_median_strength(){
        return this->m_median_player->getPlayerStrength();
    }
    void print(){
        this->m_players->printBinaryTree();
    }
};


#endif //WET24_TO_PUBLISH_TEAM_H
