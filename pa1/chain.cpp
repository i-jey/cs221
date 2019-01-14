#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  /* your code here */
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  /* your code here */
  Node * n = new Node(ndata);
  Node * last = head_->prev;
  Node * first = head_;
  n->next = first;
  n->prev = last;
  last->next = n;
  first->prev = n;
}

/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length.
 */
void Chain::moveBack(int startPos, int len, int dist){
  /* your code here */
  if(dist!=0){
    if(startPos+len-1+dist>length_){
      dist = length_-startPos-len+1;
    }
    Node * before;
    Node * after;
    Node * left;
    Node * right;
    Node * first;
    Node * last;
    Node * curr = head_;
    for(int i = 0; i < startPos+len-1+dist;i++){
      switch (i) {
        case startPos:
          first = curr;
          before = curr->prev;
          break;
        case startPos+len-1:
          last = curr;
          after = curr->next;
          break;
        case startPos+len-1+dist:
          left = curr;
          right = left->next;
          break;
      }
      curr = curr->next;
    }
    before->next = after;
    after->prev = next;
    left->next = first;
    first->prev = left;
    last->next = right;
    right->prev = last;
  }
}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
void Chain::roll(int k){
  /* your code here */
  Node * curr = head_;
  for(int i = 0; i < length_-k+1; i++){
    curr = curr->next;
  }
  Node * first = head_->next;
  Node * last = head_->prev;
  first->prev = last;
  last->next = first;
  head_->next = curr;
  head_->prev = curr->prev;
  head_->prev->next = head_;
  curr->prev = head_;
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  /* your code here */
  Node * before;
  Node * after;
  Node * curr = head_;
  for(int i = 0; i < pos2; i++){
    if(i==pos-1){
      before = curr;
    }
    curr = curr->next;
  }
  after = curr->next;
  curr = before->next;
  for(int i = 0; i <= pos2 - pos1; i++){
    Node * aux = curr->next;
    if(i==0){
      curr->next = after;
      curr->prev = aux;
    }else if(i==pos2-pos1){
      curr->next = curr->prev;
      curr->prev = before;
    }else{
      curr->next = curr->prev;
      curr->prev = aux;
    }
    curr = aux;
  }
}

/*
* Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  /* your code here */
    if(other->height_!=height_||other->width_!=width_){
      cout << "Block sizes differ." << endl;
    }else{
      Node * curr = head_->next;
      while(other->head_->next!=other->head_){ //there is still nodes
        Node * toInsert = other->head_->next;
        Node * aux = curr->next;
        toInsert->next = aux;
        toInsert->prev = curr;
        curr->next = toInsert;
        aux->prev = toInsert;
        if(curr->next->next==head_){
          curr = curr->next;
        }else{
          curr = curr->next->next;
        }
      }
    }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  /* your code here */
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  /* your code here */
}
