#include "player.h"

Player::Player(int u_value, std::string u_name){
        m_value = u_value;
        m_name = u_name;
    }
    //Getter
void Player::GetValue(){
    std::cout << m_value << "\n";
}

//Setter
void Player::SetValue(int u_value){
    m_value = u_value;
}