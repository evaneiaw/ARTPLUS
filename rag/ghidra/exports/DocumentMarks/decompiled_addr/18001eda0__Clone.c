// DocumentMarks.dll 18001eda0 DocumentMarks::BearerBar::Clone
// signature: BearerBar * Clone(BearerBar * this, CloneStrategy * param_1)

/* public: virtual class DocumentMarks::BearerBar * __ptr64 __cdecl
   DocumentMarks::BearerBar::Clone(class ArtDoc::CloneStrategy & __ptr64)const __ptr64 */

BearerBar * __thiscall DocumentMarks::BearerBar::Clone(BearerBar *this,CloneStrategy *param_1)

{
  BearerBar *pBVar1;
  
                    /* 0x1eda0  862
                       ?Clone@BearerBar@DocumentMarks@@UEBAPEAV12@AEAVCloneStrategy@ArtDoc@@@Z */
  pBVar1 = (BearerBar *)FUN_1802d6b50(0x6b8);
  if (pBVar1 == (BearerBar *)0x0) {
    return (BearerBar *)0x0;
  }
  pBVar1 = (BearerBar *)BearerBar(pBVar1,this,param_1);
  return pBVar1;
}


