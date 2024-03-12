//
// Created by raz29 on 09/03/2024.
//

#include "Team.h"

Team::Team(const int teamId): m_id(teamId) , m_size(0),m_num_of_wins(0)
, m_players(AvlTree<int ,Player*>(true)) , m_newest_player(List<Player*>()){}

Team::~Team() {
    m_newest_player.Delete_list_and_Data(); //deletes the players in the list
    m_players.deleteTreeData(m_players.getRoot()); // deletes the players in the tree
    //note : i'm not sure if i am deleting the players twice or not

}

int Team::get_size() const {
    return this->m_size;
}

void Team::set_size(const int size) {
    this->m_size = size;
}

StatusType Team::add_player(const int playerStrength) {
    if(playerStrength <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
    Player* newPlayer = new Player(this->m_id , playerStrength);
    this->m_players.insert(playerStrength , newPlayer , true);
    this->m_newest_player.addNode(newPlayer);
    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Team::remove_newest_player(const int playerStrength) {
}

int Team::getStrength() const {
    return m_median_player->getPlayerStrength() * m_size;
}

int Team::get_id() const {
    return m_id;
}
int& Team::get_id_ref(){
    return m_id;
}