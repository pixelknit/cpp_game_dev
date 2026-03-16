#pragma once

#include <iostream>

class Player{
    private:
        int m_value;
        std::string m_name;
    
    public:
        Player(int u_value, std::string u_name);

        //Getter
        void GetValue();

        //Setter
        void SetValue(int u_value);
};