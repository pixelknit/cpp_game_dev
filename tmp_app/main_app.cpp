#include <iostream>
#include <vector>
#include <unordered_map>

void AddEntity(std::vector<std::string> &players, std::string &player){
  players.push_back(player);
  std::cout << "Player added to the database\n";
}

void PrintPlayerLenght(const std::string &player){
  std::cout << player.length() << "\n";
}

void InsertIntoMap(std::string region_name,
      std::unordered_map<std::string, std::vector<std::string>> &map,
      std::vector<std::string> &players
    ){
  map.insert(std::pair<std::string, std::vector<std::string>> (region_name, players)); 
}


int main(){

  std::unordered_map<std::string, std::vector<std::string>> map {};

  std::string player1 = "MyPlayer1";
  std::string player2 = "MyPlayer22";
  std::string player3 = "MyPlayer334";

  std::vector<std::string> europe_players {};

  AddEntity(europe_players, player1);
  AddEntity(europe_players, player2);
  AddEntity(europe_players, player3);

  std::cout << "----------------------------------\n";

  for ( const std::string &player: europe_players){
    PrintPlayerLenght(player);
  }

  std::cout << "----------------------------------\n";

  std::string player4 = "MyPlayer18";
  std::string player5 = "MyPlayer2";
  std::string player6 = "MyPlayer33";

  std::vector<std::string> asian_players {};

  AddEntity(asian_players, player4);
  AddEntity(asian_players, player5);
  AddEntity(asian_players, player6);

  InsertIntoMap("Europe", map, europe_players);
  InsertIntoMap("Asia", map, asian_players);

  for (auto &x: map){
    std::cout << x.first << "\n";
    std::cout << "***********\n";
    for (auto &y: x.second){
      std::cout << y << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
