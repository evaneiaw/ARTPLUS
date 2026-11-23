// DocumentMarks.dll 180130cc0 DocumentMarks::PDFPlusBearerBar::GetDirection
// signature: Direction GetDirection(PDFPlusBearerBar * this)

/* public: enum DocumentMarks::PDFPlusBearerBar::Direction __cdecl
   DocumentMarks::PDFPlusBearerBar::GetDirection(void)const __ptr64 */

Direction __thiscall DocumentMarks::PDFPlusBearerBar::GetDirection(PDFPlusBearerBar *this)

{
                    /* 0x130cc0  1163
                       ?GetDirection@PDFPlusBearerBar@DocumentMarks@@QEBA?AW4Direction@12@XZ
                       0x130cc0  1270
                       ?GetRepeatFor@PDFPlusRepeatForGridMark@DocumentMarks@@QEBA?AW4RepeatFor@12@XZ
                        */
  return *(Direction *)(this + 0x6a8);
}


