//
// Created by raz29 on 09/03/2024.
//
#include "Team.h"
#include "math.h"


Team::Team(const int teamId): m_id(teamId) , m_size(0),m_num_of_wins(0) , m_median_player(0)
, m_newest_player(new List<int>()) , m_players(new AvlTree<int , int>()) {}

Team::~Team() {
    if (this->m_newest_player != nullptr) {
       m_newest_player->Delete_list_and_Data();//deletes the players in the list
    }
    //m_players->deleteTreeData(m_players->getRoot());
    delete m_players;
    delete m_newest_player;
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
    this->m_players->insert(playerStrength, playerStrength,0, true);
    this->m_newest_player->addNode(playerStrength);
    m_size++;
    if (m_size == 1){
        m_median_player = playerStrength;
    }else{
        set_median();
    }
    return StatusType::SUCCESS;
}

StatusType Team::remove_newest_player() {
    if(m_size == 0){
        return StatusType::FAILURE;
    }
    auto player = m_newest_player->get_head();
    m_players->remove(player, player);
    m_newest_player->pop();
    m_size--;
    if(m_size == 0){
        m_median_player = 0;
    }else{
      this->set_median();
    }
    return StatusType::SUCCESS;
}

int Team::getStrength() const {
    return m_size == 0 ? 0 : m_median_player * m_size;
}

int Team::get_id() const {
    return m_id;
}
int& Team::get_id_ref(){
    return m_id;
}

void Team::set_median() {
    if(this->get_size() == 0)
    {
        m_median_player = 0;
    }
    else if (this->get_size() == 1)
    {
        m_median_player = m_players->getRoot()->getKey();
    }
    else
    {
        int median_index = (int)floor(this->get_size() / 2);
        m_median_player = m_players->getNodeByIndex(median_index + 1)->getKey();
    }
}

AvlTree<int, int>::Key_Data_pair** Team::get_team_player_array() {
    return this->m_players->get_tree_as_array();
}


/// caller is responsible foe memory deallocation of returned value
/// \param arr1 NOT DELETED
/// \param size1
/// \param arr2 NOT DELETED
/// \param size2
Pair_Ptr_arr Team::merge_arrays_key_data_pair(Pair_Ptr_arr arr1, int size1, Pair_Ptr_arr arr2, int size2){
    int newsize= size1 + size2;
    Pair_Ptr_arr newArr = new AvlTree<int , int>::Key_Data_pair*[newsize];
    int k = 0 , l = 0;
    for (int i = 0; i < newsize ; ++i) {
        if ( k >= size1){
            newArr[i] = arr2[l++];
        }else if(l >= size2){
            newArr[i] = arr1[k++];
        }else if (arr1[k]->key <= arr2[l]->key){
            newArr[i] = arr1[k++];
        }else if (arr1[k]->key > arr2[l]->key){
            newArr[i] = arr2[l++];
        }
    }
    return newArr;
}


/// dosnt delete team2 but empties it , deletes tree nodes and list is empty
/// returns the old strength of team 2
void Team::merge_team_into_me(Team* team2) {
    if(team2 == nullptr || team2->m_size == 0){
        return;
    }
    Pair_Ptr_arr arr1 = this->get_team_player_array();
    Pair_Ptr_arr  arr2 = team2->get_team_player_array();
    Pair_Ptr_arr unite_arr = merge_arrays_key_data_pair(arr1 , this->m_size , arr2 , team2->get_size());
    size_t newSize = this->m_size +team2->get_size();
    auto newtree = create_tree_from_array(unite_arr , newSize);
    //delete old data
    for (int i = 0; i < this->m_size; ++i) {
        delete arr1[i];
    }
    delete[] arr1;
    for (int i = 0; i < team2->m_size; ++i) {
        delete arr2[i];
    }
    delete[] arr2;
//    for (int i = 0; i < newSize; ++i) {
//        delete unite_arr[i];
//    }
    delete[] unite_arr;


    //delete old data
    delete m_players; // delete old trees
    delete team2->m_players; //delete team2 tree
    m_players = nullptr;

    //replace data
    this->m_size = newSize;
    this->m_players = newtree;
    this->m_newest_player->connect_list(*team2->m_newest_player);
    team2->m_newest_player->set_head(0);

    team2->m_players = nullptr;
    team2->m_median_player = 0;
    team2->set_size(0);


    this->set_median();
}


AvlTree<int, int> *Team::create_tree_from_array(Pair_Ptr_arr arr,int size) {
    AvlTree<int ,int>* newTree = new AvlTree<int , int>;

    int height = (int)ceil(log2(size+1) ) -1 ;
    int redundant = (int)pow(2,height+1)-1-size;
    int i = 0;
    newTree->insert(0 , 0);
    aux_create_empty_tree(newTree->getRoot() , nullptr ,redundant , height);
    aux_insert_data_to_tree(newTree->getRoot() , arr , i , height , this->m_id);
    newTree->setSize(size);
    return newTree;
}

void Team::aux_create_empty_tree(TreeNode<int, int>* root ,TreeNode<int, int>* parent, int& redundant, int height) {
    root->m_parent = parent;
    root->setHeight(0);
    if (height == 0){
        root->setHeight(height);
        root->setSubTreeSize(1);
        root->m_left = nullptr;
        root->m_right = nullptr;
        return;
    }else if (height == 1 && redundant > 0){
        if (redundant == 1) {
            root->setHeight(height);
            root->setSubTreeSize(2);
            redundant--;
            root->m_right = nullptr;
            root->m_left = new TreeNode<int, int>(0, 0);
            aux_create_empty_tree(root->m_left, root, redundant, height - 1);
            return;
        }else{
            root->setHeight(0);
            root->setSubTreeSize(1);
            redundant -= 2;
            root->m_left = nullptr;
            root->m_right = nullptr;
            return;
        }
    }
    root->m_right = new TreeNode<int, int>(0 , 0);
    aux_create_empty_tree(root->m_right , root , redundant ,height - 1);

    root->m_left = new TreeNode<int, int>(0 , 0);
    aux_create_empty_tree(root->m_left , root , redundant ,height - 1);
    root->setSubTreeSize(root->m_left->getSubTreeSize() + root->m_right->getSubTreeSize() + 1 );
    root->updateHeight();
}

void Team::aux_insert_data_to_tree(TreeNode<int, int> *root, Pair_Ptr_arr arr, int &i, int height , int teamId) {
    if (root == nullptr ){
        return;
    }
    aux_insert_data_to_tree(root->m_left , arr , i , height - 1 , teamId);
    root->setKey( arr[i]->key);
    root->setData( arr[i]->data );
    i += 1;
    aux_insert_data_to_tree(root->m_right,arr,i , height - 1 , teamId);
}

void Team::add_point() {
    m_num_of_wins++;
}

bool Team::play_match(Team *team2) {
    int strength_team1 = this->getStrength();
    int strength_team2 = team2->getStrength();

    if (strength_team1 > strength_team2){
        this->add_point();
        return true;
    }else if (strength_team1 < strength_team2){
        team2->add_point();
        return false;
    }else{//strength_team1 == strength_team2
        if(this->get_id() < team2->get_id()){
            this->add_point();
            return true;
        }
    }
    team2->add_point();
    return false;
}

int Team::get_number_of_wins() const {
    return m_num_of_wins;
}

void Team::set_points(int points)
{
    m_num_of_wins = points;
}

