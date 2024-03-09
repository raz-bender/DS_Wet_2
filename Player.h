//
// Created by raz29 on 09/03/2024.
//

#ifndef WET24_TO_PUBLISH_PLAYER_H
#define WET24_TO_PUBLISH_PLAYER_H

class Player{
    int m_teamId;
    int m_player_strength;

public:
    Player(const int teamId ,const int strength): m_teamId(teamId) , m_player_strength(strength){}

    ~Player() = default;

    int getTeamId() const {
        return m_teamId;
    }

    void setTeamId(const int teamId) {
        m_teamId = teamId;
    }

    int getPlayerStrength() const {
        return m_player_strength;
    }

    void setPlayerStrength(const int strength) {
        m_player_strength = strength;
    }
};



#endif //WET24_TO_PUBLISH_PLAYER_H
