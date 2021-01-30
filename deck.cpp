//=======================================================================

#include <iostream>
#include <string>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"
#include <random>
//The DeckSize function is a simple accessor. We simply
//need to go over the list until we reach a NULL pointer
//while keeping track with an int
int DeckSize(Node* deckx) {
  int counter = 0;
  for(Node* i = deckx; i != NULL; i = i->after) {
    counter++;
  }
  return counter;
}
//Here we create a destructor implementation of type void
//so that we can prevent any memory leaks from occurring
//as a result of nodes pointing to cards in the heap
void DeleteAllCards(Node* deckx) {
  Node* temp = NULL;
  for(Node* i = deckx; i != NULL; i = temp) {
    temp = i->after;
    delete i;
  }
}
//our CutDeck function takes 3 Node pointers by reference and a string by
//value to determine which cutting method will be used. We pass the nodes
//by reference because it is as if we are taking a physical deck of cards
//and cutting it in half, we wouldnt take a deck and duplicate it just
//to cut it in half in real life!
void CutDeck(Node* &deckx, Node* &topx, Node* &bottomx, std::string type) {
  int half = 0;
  if(type == "perfect") {
    int size = DeckSize(deckx);
    //since half is type integer, it will always take care of the midpoint
    //when dealing with decks that contain an odd number of cards
    half = size / 2;
  }
  else if(type == "random") {
    half = 5;
    //finish later with randomness
    //here is where I plan to implement my random cut process
  }
  int counter = 0;
  Node* i = deckx;
  //this foor loop places our pointer at the midway point of the deck
  //then we can rearrange the pointers to form 2 separate decks
  for(; counter != half; i = i->after) {
    ++counter;

  }
  topx = i;
  bottomx = deckx;
  topx->before->after = NULL;
  topx->before = NULL;
}
//Our Shuffle function is arguably one of the most important in the
//entire homework! here we simple take a card from either half of
//a split deck and place them into a new deck while alternating sides
Node* Shuffle(Node* &bottom, Node* &top, std::string type) {
  //we have a node last so that we can access the last card we placed
  Node* newdeck = NULL;
  Node* newdeck_last = NULL;

  int totalsize;
  //calculate the size to find our stopping point
  totalsize = DeckSize(top) + DeckSize(bottom);
  //std::cout << "total size: " << totalsize << "\n";
  for(int i = 0; i < totalsize; i++) {
    //the purpose of modulus here is to determine which of the
    //two decks to place down into the new deck. since all
    //even numbers are divisible by 2, modulus is a great way
    //to switch between sides as we go
    if(i % 2 == 1) {

      Node* card;
      card = bottom;
      if(i >= totalsize - 2) {
        bottom->after = NULL;
      }
      else {
        bottom = bottom->after;
      }
      //I chose to completely seperate the card from its olf deck
      //before I placed it in its new deck, this was for simplicity
      bottom->before = NULL;
      card->before = NULL;
      card->after = NULL;
      if(newdeck == NULL && newdeck_last == NULL) {
        newdeck = card;
        newdeck_last = card;
      }
      else {
        card->before = newdeck_last;
        newdeck_last->after = card;
        newdeck_last = card;
      }
    }
    else {
      //this is the same code as above, just instead we pull
      //our card from the other deck
      Node* card;
      card = top;
      if(i >= totalsize - 2) {
        top->after = NULL;
      }
      else {
        top = top->after;
      }
      top->before = NULL;
      card->before = NULL;
      card->after = NULL;
      //Corner case in case this is the first card
      if(newdeck == NULL && newdeck_last == NULL) {
        newdeck = card;
        newdeck_last = card;
      }
      else {
        card->before = newdeck_last;
        newdeck_last->after = card;
        newdeck_last = card;
      }
    }

  }
  //since shuffle is type Node, it must return a deck
  return newdeck;
}
//here is the hardest implementation in the entire homework!
Node* SortHand(Node* deckx) {
  int size_of_deck;
  Node* head;
  Node* tail;
  Node* iterator = deckx;
  //since we do not want to have deckx point away from the beginning
  //we use iterator to do it without changing deckx
  size_of_deck = DeckSize(deckx);
  //I am setting all the sorted pointers to NULL for sorting
  for(int i = 0;i<size_of_deck;i++) {
    iterator->sorted_prev = NULL;
    iterator->sorted_next = NULL;
    iterator = iterator->after;
  }
  if(size_of_deck <= 1) {
    return deckx;
  }
  Node* smallest_card;
  //because we cannot compare NULL to cards, smallest_card by default
  //takes on the first value in deckx
  smallest_card = deckx;
  iterator = deckx->after;
  for(int j = 1;j<size_of_deck;j++) {
    //if our iterator is smaller than our smallest card, update it!
    if(iterator->getCard() < smallest_card->getCard()) {
      smallest_card = iterator;
    }
    iterator = iterator->after;
  }
  //with only one card in our sorted deck, the head and tail must be
  //the same
  head = smallest_card;
  tail = smallest_card;
  for(int i = 1;i < size_of_deck;i++) {
    smallest_card = deckx;
    iterator = deckx->after;
    for(int o = 1;o < size_of_deck;o++) {
      if(iterator->getCard() < tail->getCard() || iterator->getCard() == tail->getCard()) {
        iterator = iterator->after;
        continue;
      }
      //What is this if statement here for? well if we were to set the smallest_card to the first
      //item in our list of cards, we would be unable to move sticking us in an infinite loop
      //this allows the iterator to move in the case the first card is the smallest card
      if(smallest_card->getCard() < tail->getCard() || smallest_card->getCard() == tail->getCard()) {
        smallest_card = iterator;
        iterator = iterator->after;
        continue;
      }
      if(iterator->getCard() < smallest_card->getCard()) {
        smallest_card = iterator;
      }
      iterator = iterator->after;
    }
    tail->sorted_next = smallest_card;
    smallest_card->sorted_prev = tail;
    tail = smallest_card;
  }
  //The essential process of sort:
  //Set all the sorted pointers to null for all cards
  // Find smallest card in deck
  //Consider this card the top of the new sorted deck
  // for loop over all cards to find smallest card that has pointers that are NULL
  //ignore nodes that have sorted_next or prev not eqaul to NULL
  return head;
}

bool SamePrimaryOrder(Node* deckx1, Node* deckx2) {
  int deckxsize;
  deckxsize = DeckSize(deckx1);
  int tracker = 0;
  for(;tracker < deckxsize;tracker++) {
    //Easily return false the instant there is a card that
    //does not match
    if(deckx1->getCard().getCard() != deckx2->getCard().getCard() || deckx1->getCard().getSuit() != deckx2->getCard().getSuit()) {
      return false;
    }
    //iterate both decks forward at once to compare
    deckx1 = deckx1->after;
    deckx2 = deckx2->after;
  }
  return true;

}
bool ReversePrimaryOrder(Node* deckx1, Node* deckx2) {
  //same as the function above, except I iterate one list backwards
  //and the other forwards, which requires me to have one more loop
  //to find the tail of the deck
  int deckxsize;
  deckxsize = DeckSize(deckx1);
  int tracker = 0;
  Node* tail;
  for(int i = 0;i < deckxsize;i++) {
    if(deckx1->after == NULL) {
      tail = deckx1;
      break;
    }
    deckx1 = deckx1->after;
  }
  for(;tracker < deckxsize;tracker++) {
    if(tail->getCard().getCard() != deckx2->getCard().getCard() || tail->getCard().getSuit() != deckx2->getCard().getSuit()) {
      return false;
    }
    tail = tail->before;
    deckx2 = deckx2->after;
  }
  return true;
}
//We need to take in hands as a Node** because it is pointing to an array of pointers!
void Deal(Node* &deckx, Node** hands, int num_hands, std::string type, int cards) {
  Node* hands_last[num_hands];
  //make sure all the hands are NULL at start for simplicity
  for(int v = 0;v < num_hands;v++) {
    hands_last[v] = NULL;
  }
  for(int j = 0;j < num_hands;j++) {
    hands[j] = NULL;
  }
  if(type == "one-at-a-time") {
    int tracker = 0;
    Node* card;
    int totalcards;
    totalcards = cards * num_hands;
    for(int i = 0;i < totalcards;i++) {
      if(tracker == num_hands) {
        tracker = 0;
      }
      card = deckx;
      //covers a corner case, what if there are going to be
      //no cards left in the deck I am dealing from?
      //we cannot just iterate to nothing or we will segfault
      if(i < 51) {
        deckx = deckx->after;
        deckx->before = NULL;
      }
      else {
        deckx = NULL;
      }
      card->before = NULL;
      card->after = NULL;
      if(hands[tracker] == NULL) {
        hands[tracker] = card;
        hands_last[tracker] = card;
      }
      else {
        card->before = hands_last[tracker];
        hands_last[tracker]->after = card;
        hands_last[tracker] = card;
      }
      tracker++;
    }
  }
  else {
    std::cout << "unknown deal style" << "\n";
  }
}
//we can make clever use of the DeckPushBackCard function to create a copy of a deck.
//by retrieving the current card's data, we use DeckPushBackCard to create a new
//Node pointer with all the right data in the right spot
Node* CopyDeck(Node* deckx) {
  Node* copycopy = NULL;
  int deckxsize = DeckSize(deckx);
  int currentsize = 0;
  std::string current_suit;
  int current_card;
  Node* temp = deckx;
  for(;currentsize < deckxsize;currentsize++) {
    //since temp is pointing to Node we need to dereference it THEN call the member
    //function getSuit() and getCard()
    current_suit = temp->getCard().getSuit();
    current_card = temp->getCard().getCard();
    DeckPushBackCard(copycopy, current_suit, current_card);
    temp = temp->after;
  }
  return copycopy;

}
//this is the exact same code as PrintDeckPrimary except
//you have to change the name of the pointer
void PrintDeckSorted(const std::string &header, Node* deck) {
  std::cout << header;
  Node *tmp = deck;
  while (tmp != NULL) {
    std::cout << " " << tmp->getCard().getString();
    tmp = tmp->sorted_next;
  }
  std::cout << std::endl;
}

// ==================================================================================
