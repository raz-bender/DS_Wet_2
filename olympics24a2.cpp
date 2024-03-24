#include "olympics24a2.h"

olympics_t::olympics_t() :m_number_of_teams(0) , m_table(new HashTable<int ,Team>(hash_func)) , m_team_tree(new AvlTree<int,int>)
{

	// TODO: Your code goes here
}

olympics_t::~olympics_t()
{
	delete m_table;
    delete m_team_tree;
}


StatusType olympics_t::add_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_table->search(teamId) != nullptr){
        return StatusType::FAILURE;
    }
    try{
        Team* newTeam = new Team(teamId);
        m_table->insert(newTeam->get_id_ref() , newTeam);
        m_number_of_teams++;

    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    return remove_teamAux(teamId);
}

StatusType olympics_t::remove_teamAux(int teamId, int teamStrength)
{
    if (teamId <= 0) {
        return  StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);
    if (team == nullptr) {
        return StatusType::FAILURE;
    }

    try {
        m_team_tree->remove(teamStrength <= -1 ? team->getStrength() : teamStrength, teamId);
        m_table->remove(teamId);
        m_number_of_teams--;

    }
    catch (bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    delete team;

    return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if (teamId <= 0 || playerStrength <= 0){
        return  StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);
    if (team == nullptr){
        return StatusType::FAILURE;
    }
	try{
        if(team->get_size() == 0 && m_team_tree->find(team->getStrength(),teamId) == nullptr) {
            m_team_tree->insert(team->getStrength(),teamId);//was - m_team_tree->insert(teamId, team, playerStrength);
        }
        TreeNode<int,int>* teamNode = m_team_tree->find(team->getStrength() , team->get_id());
        team->add_player(playerStrength);
        update_team_strength_in_tree(teamNode);
        // TODO update get_highest_ranked_team

    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);

    if(team == nullptr || team->get_size() == 0){
        return  StatusType::FAILURE;
    }
    try {
        TreeNode<int,int>* teamNode = m_team_tree->find(team->getStrength() , team->get_id());

        team->remove_newest_player();

        update_team_strength_in_tree(teamNode);

    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId2 == teamId1){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_table->search(teamId1);
    Team* team2 = m_table->search(teamId2);

    if (team1 == nullptr || team2 == nullptr || team1->get_size() == 0 || team2->get_size() == 0){
        return StatusType::FAILURE;
    }

    auto team1Node = m_team_tree->find(team1->getStrength(), teamId1);
    auto team2Node = m_team_tree->find(team2->getStrength(), teamId2);

    bool is_team1_won = team1->play_match(team2);
    auto winningTeam = is_team1_won ? team1 : team2;
    auto winningTeamNode = is_team1_won ? team1Node : team2Node;
    winningTeamNode->setTeamNumOfWins(winningTeam->get_number_of_wins());
    m_team_tree->updateMaxRankRecursively(winningTeamNode);

    return is_team1_won ? teamId1 : teamId2;
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);
    if(team == nullptr){
        return StatusType::FAILURE;
    }
    TreeNode<int , int>* teamNode = m_team_tree->find(team->getStrength(),teamId);
    if (teamNode == nullptr){
        return 0; // is in hash table but not in tree
    }
    return m_team_tree->getNodeCalculatedNumOfWins(teamNode) + team->get_number_of_wins();
}

output_t<int> olympics_t::get_highest_ranked_team()
{
    if(m_table->get_size() != 0 && m_team_tree->getSize() == 0){// i.e no teams that had players
        return 0;
    }
    return m_team_tree->get_highest_ranked_team();
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId2 == teamId1){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_table->search(teamId1);
    Team* team2 = m_table->search(teamId2);
    if (team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }

    int team1OldStrength = team1->getStrength();
    int team2OldStrength = team2->getStrength();


    team1->merge_team_into_me(team2);

    this->remove_teamAux(teamId2, team2OldStrength);

    TreeNode<int, int>* team1Node = m_team_tree->find(team1OldStrength, team1->get_id());
    if (team1Node == nullptr){//team1 was always empty
        m_team_tree->insert(team1->getStrength() , team1->get_id());
        team1Node = m_team_tree->find(team1->getStrength() , team1->get_id());
        m_team_tree->updateMaxRankRecursively(team1Node);
    }
    update_team_strength_in_tree(team1Node);

    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    if (lowPower <= 0 || highPower <= 0 || lowPower >= highPower){
        return StatusType::INVALID_INPUT;
    }
    TreeNode<int ,int>* lowNode= m_team_tree->findMostLeft(lowPower);
    TreeNode<int ,int>* highNode = m_team_tree->findMostRight(highPower);
    if(lowNode == nullptr || highNode == nullptr){
        return StatusType::FAILURE;//check when is nullptr
    }

    int indexLeft = m_team_tree->getNodeIndex(lowNode); // 0
    int indexRight = m_team_tree->getNodeIndex(highNode); // 7
    int indexMid = 0;
    int amountOfTeams = indexRight - indexLeft + 1; // 7-0 + 1 = 8

    if (amountOfTeams == 0){
        return StatusType::FAILURE;
    }else if(amountOfTeams == 1){
        return highNode->getData();
    }
    if (ceil(log2(amountOfTeams)) != log2(amountOfTeams)){
        return StatusType::FAILURE;
    }
    TreeNode<int ,int>* midNode = nullptr;

    while(indexLeft < indexRight){ // 0 < 7  | 4 < 7 | 6 < 7 | 7 < 7
        indexMid = ceil((double)(indexLeft + indexRight)/2); // 7+0 /2 = 4 | (4+7)/2 = 6 | (6+7)/2 = 7
        midNode = m_team_tree->getNodeByIndex(indexMid - 1);// node index = 3 | node index = 5 | node index = 6
        m_team_tree->setValueToNodes(midNode , highNode , 1); // +1 to : 4,5,6,7 | +1 to : 6 ,7 | +1 to : 7
        m_team_tree->updateMaxRankRecursively(midNode);/// here
        m_team_tree->updateMaxRankRecursively(highNode);/// here
        //m_team_tree->printExtraTree();
        indexLeft = indexMid; // leftIndex = 4 | leftIndex = 6 | leftIndex = 7
    }

    return highNode->getData();

}

void olympics_t::update_team_strength_in_tree(TreeNode<int ,int >* teamNode){

    Team* team = m_table->search(teamNode->getData());

    int victory_points = team->get_number_of_wins() + m_team_tree->getNodeCalculatedNumOfWins(teamNode);

    m_team_tree->remove(teamNode->getKey(),team->get_id());

    team->set_points(victory_points);

    m_team_tree->insert(team->getStrength() , team->get_id(), victory_points);

}
