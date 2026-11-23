// 18024d3e0 ApplyMarksFromSet

/* public: bool __cdecl DocumentMarks::TaskMarkSets::ApplyMarksFromSet(class std::vector<class
   std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class ArtDoc::Document> >,class
   std::allocator<class std::unique_ptr<class ArtDoc::Document,struct std::default_delete<class
   ArtDoc::Document> > > > const & __ptr64,class ArtDoc::Page & __ptr64,bool) __ptr64 */

bool __thiscall
DocumentMarks::TaskMarkSets::ApplyMarksFromSet
          (TaskMarkSets *this,
          vector<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>,std::allocator<std::unique_ptr<ArtDoc::Document,std::default_delete<ArtDoc::Document>_>_>_>
          *param_1,Page *param_2,bool param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined8 *puVar4;
  
                    /* 0x24d3e0  848
                       ?ApplyMarksFromSet@TaskMarkSets@DocumentMarks@@QEAA_NAEBV?$vector@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@V?$allocator@V?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@@2@@std@@AEAVPage@ArtDoc@@_N@Z
                        */
  puVar4 = *(undefined8 **)param_1;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar4 == puVar1) {
    bVar3 = false;
  }
  else {
    do {
      puVar2 = (undefined8 *)ArtDoc::Document::GetPagesBegin((Document *)*puVar4);
      CopyMarksToPageWithLog(this,*(Page **)*puVar2,param_2,param_3);
      puVar4 = puVar4 + 1;
    } while (puVar4 != puVar1);
    bVar3 = true;
  }
  return bVar3;
}


