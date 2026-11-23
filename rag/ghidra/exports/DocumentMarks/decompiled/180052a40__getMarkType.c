// 180052a40 getMarkType

/* public: virtual class std::basic_string_view<char,struct std::char_traits<char> > __cdecl
   DocumentMarks::CutMark::getMarkType(void)const __ptr64 */

void __thiscall DocumentMarks::CutMark::getMarkType(CutMark *this)

{
  undefined8 *in_RDX;
  
                    /* 0x52a40  1956
                       ?getMarkType@CutMark@DocumentMarks@@UEBA?AV?$basic_string_view@DU?$char_traits@D@std@@@std@@XZ
                        */
  *in_RDX = "AIDynamicMarks-CutMark";
  in_RDX[1] = 0x16;
  return;
}


