/************************************************************
 * Walrus project                                        2020
 * AI parts
 *
 ************************************************************/
#include <string.h>
#include "walrus.h"
#include "..\dds-develop\include\dll.h"
#include "..\dds-develop\examples\hands.h"

void Walrus::HitByScore(DdsTricks &tr, uint made)
{
   uint row = 0, camp = 0;
   if (tr.plainScore >= made) {
      row = 1;
      camp = tr.plainScore - made;
   } else {
      camp = made - tr.plainScore - 1;
   }
   hitsCount[row][camp]++;
}

void Walrus::Score_Cumul4M(DdsTricks &tr)
{
   // "always game" strategy
   uint ideal = tr.plainScore;
   switch (ideal) {
      case 2:  cumulScore.bidGame -= 800; break;
      case 3:  cumulScore.bidGame -= 700; break;
      case 4:  cumulScore.bidGame -= 600; break;
      case 5:  cumulScore.bidGame -= 500; break;
      case 6:  cumulScore.bidGame -= 400; break;
      case 7:  cumulScore.bidGame -= 300; break;
      case 8:  cumulScore.bidGame -= 200; break;
      case 9:  cumulScore.bidGame -= 100; break;
      case 10: cumulScore.bidGame += 620; break;
      case 11: cumulScore.bidGame += 650; break;
      case 12: cumulScore.bidGame += 680; break;
      case 13: cumulScore.bidGame += 710; break;
   }

   // "always partscore" strategy
   int partdelta = ideal > 6 ? 50 + (ideal - 6) * 30 : -100;
   cumulScore.partscore += partdelta;

   // "ideal"
   if (ideal < 10) {
      cumulScore.ideal += partdelta;
   } else {
      cumulScore.ideal += 620 + (ideal-10)*30;
   }
}

void Walrus::Score_CumulNV4M(DdsTricks &tr)
{
	// "always game" strategy
	uint ideal = tr.plainScore;
	switch (ideal) {
		case 2:  cumulScore.bidGame -= 400; break;
		case 3:  cumulScore.bidGame -= 350; break;
		case 4:  cumulScore.bidGame -= 300; break;
		case 5:  cumulScore.bidGame -= 250; break;
		case 6:  cumulScore.bidGame -= 200; break;
		case 7:  cumulScore.bidGame -= 150; break;
		case 8:  cumulScore.bidGame -= 100; break;
		case 9:  cumulScore.bidGame -= 50; break;
		case 10: cumulScore.bidGame += 420; break;
		case 11: cumulScore.bidGame += 450; break;
		case 12: cumulScore.bidGame += 480; break;
		case 13: cumulScore.bidGame += 510; break;
	}

	// "always partscore" strategy
	int partdelta = ideal > 6 ? 50 + (ideal - 6) * 30 : -50;
	cumulScore.partscore += partdelta;

	// "ideal"
	if (ideal < 10) {
		cumulScore.ideal += partdelta;
	} else {
		cumulScore.ideal += 420 + (ideal - 10) * 30;
	}
}

void Walrus::Score_Cumul3NT(DdsTricks &tr)
{
   // "always game" strategy
   uint ideal = tr.plainScore;
   switch (ideal) {
      case 2:  cumulScore.bidGame -= 700; break;
      case 3:  cumulScore.bidGame -= 600; break;
      case 4:  cumulScore.bidGame -= 500; break;
      case 5:  cumulScore.bidGame -= 400; break;
      case 6:  cumulScore.bidGame -= 300; break;
      case 7:  cumulScore.bidGame -= 200; break;
      case 8:  cumulScore.bidGame -= 100; break;
      case 9:  cumulScore.bidGame += 600; break;
      case 10: cumulScore.bidGame += 630; break;
      case 11: cumulScore.bidGame += 660; break;
      case 12: cumulScore.bidGame += 690; break;
      case 13: cumulScore.bidGame += 720; break;
   }

   // "always partscore" strategy
   int partdelta = ideal > 6 ? 90 + (ideal - 7) * 30 : -100;
   cumulScore.partscore += partdelta;

   // "ideal"
   if (ideal < 9) {
      cumulScore.ideal += partdelta;
   } else {
      cumulScore.ideal += 600 + (ideal - 9) * 30;
   }
}

void Walrus::Score_CumulNV6M(DdsTricks &tr)
{
   // "always slam" strategy
   uint ideal = tr.plainScore;
   switch (ideal) {
      case 2:  cumulScore.bidSlam -=  450; break;
      case 3:  cumulScore.bidSlam -=  350; break;
      case 4:  cumulScore.bidSlam -=  400; break;
      case 5:  cumulScore.bidSlam -=  350; break;
      case 6:  cumulScore.bidSlam -=  300; break;
      case 7:  cumulScore.bidSlam -=  250; break;
      case 8:  cumulScore.bidSlam -=  200; break;
      case 9:  cumulScore.bidSlam -=  150; break;
      case 10: cumulScore.bidSlam -=  100; break;
      case 11: cumulScore.bidSlam -=   50; break;
      case 12: cumulScore.bidSlam +=  980; break;
      case 13: cumulScore.bidSlam += 1010; break;
   }

   // "always game" strategy
   int gameDelta = ideal > 9 ? 300 + (ideal - 6) * 30 : -100;
   cumulScore.bidGame += gameDelta;

   // "ideal"
   if (ideal < 12) {
      cumulScore.ideal += gameDelta;
   } else {
      cumulScore.ideal += 980 + (ideal - 12) * 30;
   }
}

void Walrus::Score_4Major(DdsTricks &tr)
{
   // hits
   HitByScore(tr, 10);

   // cumul
   Score_Cumul4M(tr);
}

void Walrus::Score_NV_4Major(DdsTricks &tr)
{
	// hits
	HitByScore(tr, 10);

	// cumul
	Score_CumulNV4M(tr);
}

void Walrus::Score_3NT(DdsTricks &tr)
{
   // hits
   HitByScore(tr, 9);

   // cumul
   Score_Cumul3NT(tr);
}

void Walrus::Score_3MajorDoubled(DdsTricks &tr)
{
  // we don't need any hits; need only a cumulative score
  cumulScore.Opp_3Major(cumulScore.oppContract,   tr.plainScore);
  cumulScore.Opp_3MajX (cumulScore.oppCtrDoubled, tr.plainScore);
}

void Walrus::Score_NV6Major(DdsTricks &tr)
{
   // hits
   HitByScore(tr, 12);

   // cumul
   Score_CumulNV6M(tr);
}

