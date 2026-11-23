// DocumentMarks.dll 18012ff70 DocumentMarks::PDFPlusBearerBar::CollectGrids
// signature: void CollectGrids(PDFPlusBearerBar * this, Content * param_1)

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl DocumentMarks::PDFPlusBearerBar::CollectGrids(class ArtDoc::Content const &
   __ptr64) __ptr64 */

void __thiscall
DocumentMarks::PDFPlusBearerBar::CollectGrids(PDFPlusBearerBar *this,Content *param_1)

{
  undefined1 auStack_d8 [32];
  undefined **local_b8;
  PDFPlusBearerBar *local_b0;
  undefined ***local_80;
  undefined **local_68;
  undefined **local_60 [7];
  undefined ***local_28;
  ulonglong local_18;
  
                    /* 0x12ff70  897
                       ?CollectGrids@PDFPlusBearerBar@DocumentMarks@@QEAAXAEBVContent@ArtDoc@@@Z */
  local_18 = DAT_180418e00 ^ (ulonglong)auStack_d8;
  if (*(longlong *)(this + 0x738) != *(longlong *)(this + 0x740)) {
    *(longlong *)(this + 0x740) = *(longlong *)(this + 0x738);
  }
  local_b8 = std::
             _Func_impl_no_alloc<`public:_void___cdecl_DocumentMarks::PDFPlusBearerBar::CollectGrids(ArtDoc::Content_const&___ptr64)___ptr64'::`2'::<lambda_1>,bool,ArtDoc::Group_const&___ptr64>
             ::vftable;
  local_80 = &local_b8;
  local_b0 = this;
  ArtDoc::ConstVisitorBase::ConstVisitorBase((ConstVisitorBase *)&local_68);
  local_68 = ArtDoc::SimpleVisitor<ArtDoc::Group_const_>::vftable;
  local_28 = (undefined ***)0x0;
  if (local_80 != (undefined ***)0x0) {
    if (local_80 == &local_b8) {
      local_28 = (undefined ***)(*(code *)(*local_80)[1])(local_80,local_60);
      if (local_80 == (undefined ***)0x0) goto LAB_180130036;
      (*(code *)(*local_80)[4])
                (local_80,CONCAT71((int7)((ulonglong)&local_b8 >> 8),local_80 != &local_b8));
    }
    else {
      local_28 = local_80;
    }
    local_80 = (undefined ***)0x0;
  }
LAB_180130036:
  (**(code **)(*(longlong *)param_1 + 8))(param_1,&local_68);
  if (local_28 != (undefined ***)0x0) {
    (*(code *)(*local_28)[4])
              (local_28,CONCAT71((int7)((ulonglong)local_60 >> 8),local_28 != local_60));
    local_28 = (undefined ***)0x0;
  }
  ArtDoc::ConstVisitorBase::~ConstVisitorBase((ConstVisitorBase *)&local_68);
  return;
}


