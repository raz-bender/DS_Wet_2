#include "olympics24a2.h"

olympics_t::olympics_t() :m_number_of_teams(0) , m_table(new HashTable<int ,Team>(hash_func)) , m_team_tree(new AvlTree<int,Team*>)
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
	try{
        Team* newTeam = new Team(teamId);
        m_table->insert(newTeam->get_id_ref() , newTeam);
        m_team_tree->insert(newTeam->getStrength() , newTeam);
        m_number_of_teams++;

    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    if (teamId <= 0){
        return  StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);
    if (team == nullptr){
        return StatusType::FAILURE;
    }

    m_team_tree->remove(teamId);
	// TODO: check if the tree updated its fields correctly in accordance to init logic

    m_table->remove(teamId);///here
    delete team;
    m_number_of_teams--;

	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if (teamId <= 0 || playerStrength <= 0){
        return  StatusType::INVALID_INPUT;
    }
    Team* team = m_table->search(teamId);/// here
    if (team == nullptr){
        return StatusType::FAILURE;
    }
	try{
        team->add_player(playerStrength);
        // TODO need to update the tree before exiting function
        // todo raz 15/03
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
    Team* team = m_table->search(teamId);/// here

    if(team == nullptr || team->get_size() == 0){
        return  StatusType::FAILURE;
    }
    team->remove_newest_player();

    // TODO update the tree after change in team strength
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
    bool is_team1_won = team1->play_match(team2);
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
    TreeNode<int , Team*>* teamNode = m_team_tree->find(teamId);
    if (teamNode == nullptr){
        return 0; // is in hash but not in tree
    }

    return m_team_tree->getNodeCalculatedValue(teamNode);

//    static int i = 0; // ???????
//    return (i++==0) ? 11 : 2;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
	// TODO: Your code goes here
    return 42;
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
    team1->merge_team_into_me(team2);

	// TODO update the tree after change in team1 strength
    // todo team2 is now empty but needs to get deleted

    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}
