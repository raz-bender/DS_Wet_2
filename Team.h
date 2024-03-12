//
// Created by raz29 on 09/03/2024.
//

#ifndef WET24_TO_PUBLISH_TEAM_H
#define WET24_TO_PUBLISH_TEAM_H
#include "AvlTree.h"
#include "list.h"
#include "wet2util.h"
#include "Player.h"

class Team {
    int m_id;
    int m_size;
    int m_num_of_wins;
    Player* m_median_player;

    //strength player
    AvlTree<int ,Player*> m_players;
    List<Player*> m_newest_player;

public:
    Team(int teamId);
    ~Team();

    int get_size() const;
    void set_size(int size);

    int &get_id_ref();
    int get_id()const;

    StatusType add_player(int playerStrength);
    StatusType remove_newest_player(int playerStrength);

    int getStrength() const;
};


#endif //WET24_TO_PUBLISH_TEAM_H
