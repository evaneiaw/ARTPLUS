// DocumentMarks.dll 180170c20 FUN_180170c20
// signature: undefined FUN_180170c20(void)

void FUN_180170c20(undefined8 *param_1,char *param_2)

{
  GADict *this;
  PDFPlusBearerBar *this_00;
  GANumber *this_01;
  bool bVar1;
  GAName *this_02;
  SizeReference SVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  GName local_res8 [16];
  GName local_res18 [8];
  double local_res20;
  GName local_38 [32];
  
  this = (GADict *)*param_1;
  GName::GName(local_res18,param_2);
  GADict::GetDict(this,local_res8);
  this_00 = (PDFPlusBearerBar *)param_1[1];
  GName::GName((GName *)&local_res20,"Reference");
  this_02 = (GAName *)GADict::GetName((GADict *)local_res8,local_38);
  bVar1 = GAName::operator==(this_02,"LeftMostGridLayout");
  if (bVar1) {
    SVar2 = 1;
  }
  else {
    bVar1 = GAName::operator==(this_02,"RightMostGridLayout");
    if (bVar1) {
      SVar2 = 2;
    }
    else {
      bVar1 = GAName::operator==(this_02,"LeftMostGridLayoutColumn");
      if (bVar1) {
        SVar2 = 3;
      }
      else {
        bVar1 = GAName::operator==(this_02,"RightMostGridLayoutColumn");
        if (bVar1) {
          SVar2 = 4;
        }
        else {
          bVar1 = GAName::operator==(this_02,"TopMostGridLayout");
          if (bVar1) {
            SVar2 = 5;
          }
          else {
            bVar1 = GAName::operator==(this_02,"BottomMostGridLayout");
            if (bVar1) {
              SVar2 = 6;
            }
            else {
              bVar1 = GAName::operator==(this_02,"TopMostGridLayoutRow");
              if (bVar1) {
                SVar2 = 7;
              }
              else {
                bVar1 = GAName::operator==(this_02,"BottomMostGridLayoutRow");
                SVar2 = -(uint)bVar1 & 8;
              }
            }
          }
        }
      }
    }
  }
  DocumentMarks::PDFPlusBearerBar::SetSizeReference(this_00,SVar2);
  GAName::~GAName((GAName *)local_38);
  uVar4 = 0;
  uVar5 = 0;
  GName::GName((GName *)&local_res20,"Extends");
  bVar1 = GADict::Has((GADict *)local_res8,(GName *)&local_res20);
  if (bVar1) {
    GName::GName((GName *)&local_res20,"Extends");
    this_01 = (GANumber *)GADict::GetNumber((GADict *)local_res8,local_38);
    dVar3 = GANumber::Get(this_01);
    uVar4 = SUB84(dVar3,0);
    uVar5 = (undefined4)((ulonglong)dVar3 >> 0x20);
    GANumber::~GANumber((GANumber *)local_38);
  }
  local_res20 = (double)CONCAT44(uVar5,uVar4) * (double)param_1[2] * DAT_1803066e0;
  DocumentMarks::PDFPlusBearerBar::SetExtend
            ((PDFPlusBearerBar *)param_1[1],
             (CoordinateBase<YAGL::MilliPointCoordinateSystem,1> *)&local_res20);
  GADict::~GADict((GADict *)local_res8);
  return;
}


