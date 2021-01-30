#include "playing_card.h"
#include "node.h"
#include <string>
// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
int DeckSize(Node* deckx);
void DeleteAllCards(Node* deckx);
void CutDeck(Node* &deckx, Node* &topx, Node* &bottomx, std::string type);
Node* Shuffle(Node* &bottom, Node* &top, std::string type);
void Deal(Node* &deckx, Node** hands, int num_hands, std::string type, int cards);
Node* SortHand(Node* deckx);
void PrintDeckSorted(const std::string &header, Node* deckx);
Node* CopyDeck(Node* deckx);
bool ReversePrimaryOrder(Node* deckx1, Node* deckx2);
bool SamePrimaryOrder(Node* deckx1, Node* deckx2);
//
// ==================================================================================
