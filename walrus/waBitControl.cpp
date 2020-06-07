/************************************************************
* Walrus project                                        2019
* Split bits part -- variant for layout-twelve
*
************************************************************/
#include "walrus.h"

#ifdef SBITS_LAYOUT_TWELVE

inline bool twSuit::HasDeuce()
{
   // count top 12 bits
   uint y = (w & 0x5550) + ((w & 0xAAA0) >> 1);
   uint z = (y & 0x3333) + ((y & 0xCCCC) >> 2);
   y      = (z & 0x0F0F) + ((z & 0xF0F0) >> 4);
   z      = (y & 0x00FF) + ((y & 0xFF00) >> 8);

   // count is greater => deuce
   return Count() > z;
}

uint twSuit::Decrypt()
{
   uint holding = (w & 0xFFF0) >> 1;
   if (HasDeuce()) {
      holding |= R2;
   }
   return holding;
}

static char ranks[] = { /*'2',*/ '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' }; // only twelve, yes
int Walrus::InitSuit(u64 suit, int idx)
{
   // put deuce 
   deck[idx++].card.jo = suit;

   // put others
   u64 bitRank = suit << 4;
   for each (char r in ranks) {
      deck[idx++].card.jo = bitRank | suit;
      bitRank <<= 1;
   }
   return idx;
}

SplitBits::SplitBits(uint hld, uint waPos)
{
   // layout is very similar
   uint x = hld << 1;

   // count bits in top 13 positions
   uint y = (hld & 0x5555) +  (x & 0x5555);
   uint z = (y   & 0x3333) + ((y & 0xCCCC) >> 2);
   y      = (z   & 0x0F0F) + ((z & 0xF0F0) >> 4);
   z      = (y   & 0x00FF) + ((y & 0xFF00) >> 8);

   // forget the deuce bit. combine result
   y = (x & 0xFFF0) + z;
   card.jo = ((u64)y) << waPos;
}

twlHCP::twlHCP(SplitBits &hand)
{
   // take 8 for aces, 4 for kings, 2 for queens, 1 for jacks
   u64 x =  hand.card.jo & 0xF000F000F000F000LL; 

   // sub 4 for aces, 1 for kings
   u64 y = (hand.card.jo & 0x8000800080008000LL) >> 1;
   u64 z = (hand.card.jo & 0x4000400040004000LL) >> 2;
   x -= y + z; 

   // fill out
   s = (uint)((x & 0xF000000000000000LL) >> (12 + 48));
   h = (uint)((x & 0x0000F00000000000LL) >> (12 + 32));
   d = (uint)((x & 0x00000000F0000000LL) >> (12 + 16));
   c = (uint)((x & 0x000000000000F000LL) >>  12);
   total = s + h + d + c;
}

twLengths::twLengths(SplitBits &hand)
{
   s = (uint)((hand.card.jo & 0x000F000000000000LL) >> 48);
   h = (uint)((hand.card.jo & 0x0000000F00000000LL) >> 32);
   d = (uint)((hand.card.jo & 0x00000000000F0000LL) >> 16);
   c = (uint)((hand.card.jo & 0x000000000000000FLL) );
}

#endif // SBITS_LAYOUT_TWELVE


