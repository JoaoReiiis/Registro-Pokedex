#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct pokemon {
  int id;
  char nome[16];
  char tipo[16];
  char tipo2[16];
  int total;
  int hp;
  int ataque;
  int defesa;
  int spataque;
  int spdefesa;
  int speed;
  int geracao;
  bool lendario;
};

void exibirAscii() {
  cout << R"(
                     ⢠⣤⣶⣿⣷⣤⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣶⣶⣾⡿⠃⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣧⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣷⣦⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀
⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣄⡀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀
⢀⣾⣿⣿⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⢀⣠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀
⣼⣿⣿⣿⠟⠋⠁⠀⠀⠀⠈⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣠⣿⣿⣿⣿⣿⣿⣄⣤⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀
⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⠟⠛⠛⢛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠻⣿⣿⣿⣿⣿⣿⡆
⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⠋⠀⠀⣀⣴⣾⡿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⢰⣿⣿⠻⣿⣿⣿⣧
⠈⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣇⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠈⢻⣿⣿⣿⣿⡿⠃⠀⠀⠀⢸⣿⣿⡆⠈⢿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⢿⣿⡟⢿⣿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⢀⣾⡿⣿⣿⠿⣿⠀⠀⠀⠀⣸⣿⣿⣷⠀⠸⣿⡿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠀⠘⠉⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠙⠁⠸⠟⠀⠀⠀⠀⠀⢸⣿⣿⣿⣧⣄⠀⣿⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⠿⠋⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀⣠⣼⠟⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⣀⣤⣴⣶⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠟⠛⠛⠉⠉⠉⠉⠉⠛⠛⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⡋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⢹⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠿⢿⣿⣿⣿⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⢹⡟⠙⠻⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠈⠀
 _____    ____   _  __ ______  _____   ______ __   __
 |  __ \  / __ \ | |/ /|  ____||  __ \ |  ____|\ \ / /
 | |__) || |  | || ' / | |__   | |  | || |__    \ V /
 |  ___/ | |  | ||  <  |  __|  | |  | ||  __|    > <
 | |     | |__| || . \ | |____ | |__| || |____  / . \
 |_|      \____/ |_|\_\|______||_____/ |______|/_/ \_\
)" << endl;
}

void exibir_menu() {
  cout << "================= MENU POKEDEX =================" << endl;
  cout << "1. Exibir Todos Pokemons" << endl;
  cout << "2. Adicionar Pokemon" << endl;
  cout << "3. Excluir Pokemon" << endl;
  cout << "4. Buscar Pokemon" << endl;
  cout << "5. Ordenar Pokemons" << endl;
  cout << "6. Salvar em arquivo" << endl;
  cout << "7. Exibir de X a Y" << endl;
  cout << "8. Limpar Tela" << endl;
  cout << "0. Sair" << endl;
  cout << "================================================" << endl;
  cout << "Escolha uma opcao: ";
}

bool inicializar_pokedex(pokemon *&pokedex, int &tamPokedex, int &tamMax,
                         int margem, string &cabecalho,
                         const string &nomeArquivo) {

  ifstream entrada(nomeArquivo);
  if (!entrada.is_open()) {
    cout << "Erro ao abrir o arquivo texto: " << nomeArquivo << endl;
    return false;
  }

  getline(entrada, cabecalho);
  entrada >> tamPokedex;

  tamMax = tamPokedex + margem;
  pokedex = new pokemon[tamMax];

  for (int i = 0; i < tamPokedex; i++) {
    entrada >> pokedex[i].id;
    entrada.ignore();
    entrada.getline(pokedex[i].nome, sizeof(pokedex[i].nome), ',');
    entrada.getline(pokedex[i].tipo, sizeof(pokedex[i].tipo), ',');
    entrada.getline(pokedex[i].tipo2, sizeof(pokedex[i].tipo2), ',');
    entrada >> pokedex[i].total;
    entrada.ignore();
    entrada >> pokedex[i].hp;
    entrada.ignore();
    entrada >> pokedex[i].ataque;
    entrada.ignore();
    entrada >> pokedex[i].defesa;
    entrada.ignore();
    entrada >> pokedex[i].spataque;
    entrada.ignore();
    entrada >> pokedex[i].spdefesa;
    entrada.ignore();
    entrada >> pokedex[i].speed;
    entrada.ignore();
    entrada >> pokedex[i].geracao;
    entrada.ignore();
    entrada >> pokedex[i].lendario;
  }

  entrada.close();

  cout << "Arquivo texto lido!" << endl;
  return true;
}

bool inicializar_pokedex_binario(pokemon *&pokedex, int &tamPokedex,
                                 int &tamMax, int margem,
                                 const string &nomeArquivoBinario) {

  ifstream entrada(nomeArquivoBinario, ios::binary);

  if (!entrada) {
    cout << "Sem arquivo binário." << endl;
    return false;
  }

  entrada.seekg(0, ios::end);
  size_t tamanhoArquivo = entrada.tellg();
  entrada.seekg(0, ios::beg);

  tamPokedex = tamanhoArquivo / sizeof(pokemon);
  pokedex = new pokemon[tamPokedex];

  entrada.read((char *)pokedex, tamanhoArquivo);
  entrada.close();

  cout << "Arquivo binário lido!" << endl;
  return true;
}

void salva_arquivo(pokemon *pokedex, int tamPokedex, string cabecalho) {
  cout << "Digite o nome do arquivo para salvar os dados em texto: ";
  string nomeArquivo;
  cin >> nomeArquivo;

  ofstream saida(nomeArquivo);

  saida << cabecalho << endl;
  saida << tamPokedex << endl;
  for (int i = 0; i < tamPokedex; i++) {
    saida << pokedex[i].id << "," << pokedex[i].nome << "," << pokedex[i].tipo
          << "," << (pokedex[i].tipo2[0] == '\0' ? "" : pokedex[i].tipo2) << ","
          << pokedex[i].total << "," << pokedex[i].hp << ","
          << pokedex[i].ataque << "," << pokedex[i].defesa << ","
          << pokedex[i].spataque << "," << pokedex[i].spdefesa << ","
          << pokedex[i].speed << "," << pokedex[i].geracao << ","
          << pokedex[i].lendario << endl;
  }

  saida.close();
}

void salva_arquivo_binario(pokemon *pokedex, int tamPokedex) {
  cout << "Digite o nome do arquivo para salvar os dados em binario: ";
  string nomeArquivo;
  cin >> nomeArquivo;

  ofstream saida(nomeArquivo);

  saida.write((const char *)pokedex, sizeof(pokemon) * tamPokedex);
  saida.close();
}

void adiciona(pokemon *&pokedex, int &tamPokedex, int &tamMax, int margem) {
  if (tamPokedex >= tamMax) {
    tamMax += margem;
    pokemon *novoPokedex = new pokemon[tamMax];

    for (int i = 0; i < tamPokedex; i++) {
      novoPokedex[i] = pokedex[i];
    }

    delete[] pokedex;
    pokedex = novoPokedex;
  }

  pokemon novoPokemon;

  cout << "Digite os dados do novo Pokémon:" << endl;

  cout << "ID: ";
  cin >> novoPokemon.id;
  cin.ignore();

  cout << "Nome: ";
  cin.getline(novoPokemon.nome, sizeof(novoPokemon.nome));

  cout << "Tipo 1: ";
  cin.getline(novoPokemon.tipo, sizeof(novoPokemon.tipo));

  cout << "Tipo 2 (deixe em branco se não houver): ";
  cin.getline(novoPokemon.tipo2, sizeof(novoPokemon.tipo2));

  cout << "HP: ";
  cin >> novoPokemon.hp;

  cout << "Ataque: ";
  cin >> novoPokemon.ataque;

  cout << "Defesa: ";
  cin >> novoPokemon.defesa;

  cout << "SpAtaque: ";
  cin >> novoPokemon.spataque;

  cout << "SpDefesa: ";
  cin >> novoPokemon.spdefesa;

  cout << "Speed: ";
  cin >> novoPokemon.speed;

  novoPokemon.total = novoPokemon.hp + novoPokemon.ataque + novoPokemon.defesa +
                      novoPokemon.spataque + novoPokemon.spdefesa +
                      novoPokemon.speed;

  cout << "Geração: ";
  cin >> novoPokemon.geracao;

  cout << "Lendário (1 para sim, 0 para não): ";
  cin >> novoPokemon.lendario;

  pokedex[tamPokedex] = novoPokemon;
  tamPokedex++;
}

void exclui(pokemon *&pokedex, int &tamPokedex, int &tamMax, int margem) {
  int idExcluir;
  cout << "Digite o ID do Pokémon a ser excluído: ";
  cin >> idExcluir;

  int indice = -1;
  for (int i = 0; i < tamPokedex; i++) {
    if (pokedex[i].id == idExcluir) {
      indice = i;
    }
  }

  if (indice == -1) {
    cout << "Pokémon com ID " << idExcluir << " não encontrado." << endl;
    return;
  }

  for (int i = indice; i < tamPokedex - 1; i++) {
    pokedex[i] = pokedex[i + 1];
  }

  tamPokedex--;
  cout << "Pokémon com ID " << idExcluir << " foi excluído." << endl;

  if (tamPokedex < tamMax - margem) {
    tamMax -= margem;
    pokemon *novoPokedex = new pokemon[tamMax];

    for (int i = 0; i < tamPokedex; i++) {
      novoPokedex[i] = pokedex[i];
    }

    delete[] pokedex;
    pokedex = novoPokedex;
  }
}

bool compara(pokemon x, pokemon y, int campo, bool crescente) {
  switch (campo) {
  case 1:
    return crescente ? x.id < y.id : x.id > y.id;
    break;
  case 2:
    return crescente ? strcmp(x.nome, y.nome) < 0 : strcmp(x.nome, y.nome) > 0;
    break;
  case 3:
    return crescente ? x.total < y.total : x.total > y.total;
    break;
  case 4:
    return crescente ? x.hp < y.hp : x.hp > y.hp;
    break;
  case 5:
    return crescente ? x.ataque < y.ataque : x.ataque > y.ataque;
    break;
  case 6:
    return crescente ? x.defesa < y.defesa : x.defesa > y.defesa;
    break;
  case 7:
    return crescente ? x.spataque < y.spataque : x.spataque > y.spataque;
    break;
  case 8:
    return crescente ? x.spdefesa < y.spdefesa : x.spdefesa > y.spdefesa;
    break;
  case 9:
    return crescente ? x.speed < y.speed : x.speed > y.speed;
    break;
  default:
    return false;
    break;
  }
}

void quicksort(pokemon *pokedex, int inicio, int fim, int campo,
               bool crescente) {
  if (inicio > fim)
    return;

  int pivoIndex = inicio;
  pokemon pivo = pokedex[fim];

  for (int i = inicio; i < fim; i++) {
    if (compara(pokedex[i], pivo, campo, crescente)) {
      swap(pokedex[i], pokedex[pivoIndex]);
      pivoIndex++;
    }
  }

  swap(pokedex[pivoIndex], pokedex[fim]);

  quicksort(pokedex, inicio, pivoIndex - 1, campo, crescente);
  quicksort(pokedex, pivoIndex + 1, fim, campo, crescente);
}

pokemon *busca_binaria(pokemon *pokedex, int inicio, int fim, const char *nome,
                       int id) {
  if (inicio > fim)
    return nullptr;

  int meio = (inicio + fim) / 2;

  if (nome == nullptr) {
    if (pokedex[meio].id == id) {
      return &pokedex[meio];
    } else if (pokedex[meio].id < id) {
      return busca_binaria(pokedex, meio + 1, fim, nome, id);
    } else {
      return busca_binaria(pokedex, inicio, meio - 1, nome, id);
    }
  } else {
    if (strcmp(pokedex[meio].nome, nome) == 0) {
      return &pokedex[meio];
    } else if (strcmp(pokedex[meio].nome, nome) < 0) {
      return busca_binaria(pokedex, meio + 1, fim, nome, id);
    } else {
      return busca_binaria(pokedex, inicio, meio - 1, nome, id);
    }
  }
}

string pokemonToString(pokemon &pokemon) {
  return "ID: " + to_string(pokemon.id) + ", Nome: " + string(pokemon.nome) +
         ", Tipo: " + string(pokemon.tipo) +
         (pokemon.tipo2[0] != '\0' ? ", Tipo2: " + string(pokemon.tipo2) : "") +
         ", Total: " + to_string(pokemon.total) +
         ", HP: " + to_string(pokemon.hp) +
         ", Ataque: " + to_string(pokemon.ataque) +
         ", Defesa: " + to_string(pokemon.defesa) +
         ", SpAtaque: " + to_string(pokemon.spataque) +
         ", SpDefesa: " + to_string(pokemon.spdefesa) +
         ", Velocidade: " + to_string(pokemon.speed) +
         ", Geração: " + to_string(pokemon.geracao) +
         ", Lendário: " + (pokemon.lendario ? "Sim" : "Não");
}

int main() {
  string cabecalho;
  int tamPokedex;
  int margem = 5;
  int tamMax;
  pokemon *pokedex = nullptr;

  string nomeArquivoCSV = "Pokemon.csv";
  string nomeArquivoBinario = "Pokemon.bin";

  if (!inicializar_pokedex_binario(pokedex, tamPokedex, tamMax, margem,
                                   nomeArquivoBinario))
    inicializar_pokedex(pokedex, tamPokedex, tamMax, margem, cabecalho,
                        nomeArquivoCSV);

  exibirAscii();
  int opcao = 0;
  do {
    exibir_menu();
    cin >> opcao;

    switch (opcao) {
    case 1: {
      for (int i = 0; i < tamPokedex; i++) {
        cout << pokemonToString(pokedex[i]) << endl;
      }
      break;
    }

    case 2: {
      adiciona(pokedex, tamPokedex, tamMax, margem);
      break;
    }

    case 3: {
      exclui(pokedex, tamPokedex, tamMax, margem);
      break;
    }

    case 4: {
      cout << "Deseja buscar por (0) Nome ou (1) Id? ";
      int opcaoBusca;
      cin >> opcaoBusca;

      if (opcaoBusca) {
        int id;
        cout << "Digite o ID do Pokemon: ";
        cin >> id;
        quicksort(pokedex, 0, tamPokedex - 1, 1, 1);
        pokemon *busca = busca_binaria(pokedex, 0, tamPokedex - 1, nullptr, id);
        busca == nullptr ? cout << "Pokemon nao encontrado." << endl
                         : cout << pokemonToString(*busca) << endl;
      } else {
        char nome[16];
        cout << "Digite o Nome do Pokemon: ";
        cin.ignore();
        cin.getline(nome, sizeof(nome));
        quicksort(pokedex, 0, tamPokedex - 1, 2, 1);
        pokemon *busca = busca_binaria(pokedex, 0, tamPokedex - 1, nome, 0);
        busca == nullptr ? cout << "Pokemon nao encontrado." << endl
                         : cout << pokemonToString(*busca) << endl;
      }
      break;
    }

    case 5: {
      int campo;
      bool crescente;

      cout << "Por qual campo deseja ordenar? (opções: (1) id, (2) nome, (3) "
              "total, (4) hp, (5) ataque, (6) defesa, (7) spataque, (8) "
              "spdefesa, (9) speed): ";
      cin >> campo;

      cout << "Deseja ordenar de forma crescente? (1 para sim, 0 para não): ";
      cin >> crescente;

      quicksort(pokedex, 0, tamPokedex - 1, campo, crescente);

      cout << "Pokémons ordenados com sucesso!" << endl;
      break;
    }

    case 6: {
      salva_arquivo(pokedex, tamPokedex, cabecalho);
      salva_arquivo_binario(pokedex, tamPokedex);
      break;
    }

    case 7: {
      int comeco;
      int fim;

      cout << "Digite o elemento que voce deseja comecar: ";
      cin >> comeco;
      cout << "Agora digite o elemento que voce deseja terminar: ";
      cin >> fim;

      for (int i = comeco - 1; i < fim; i++) {
        cout << pokemonToString(pokedex[i]) << endl;
      }
      break;
    }
    
    case 8:
      system("clear||cls");
      exibirAscii();
      break;
    case 0:
      cout << "Encerrando o programa. Até logo!" << endl;
      break;
    default:
      cout << "Opcao invalida! Tente novamente." << endl;
    }

  } while (opcao != 0);

  delete[] pokedex;
  return 0;
}