unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, JvTrayIcon, JvComponentBase, ImgList, Registry,
  Menus, StdCtrls, XPMan, ExtCtrls, jpeg, JvExControls, JvPoweredBy,
  shellapi, JvExExtCtrls, MMSystem, About_f, iaRS232, Vcl.ExtDlgs, pngimage,
  ShlObj, IdAuthentication, IdBaseComponent, IdComponent, IdTCPConnection,
  IdTCPClient, IdHTTP, IdIOHandler, IdIOHandlerSocket, IdIOHandlerStack, IdSSL,
  IdSSLOpenSSL, IdMultipartFormData, System.DateUtils;

type
  TmainFrm = class(TForm)
    MyTray: TJvTrayIcon;
    TrayMenu: TPopupMenu;
    AutoStartupBtn: TMenuItem;
    ExitBtn: TMenuItem;
    AboutBtn: TMenuItem;
    OKBtn: TButton;
    XPManifest1: TXPManifest;
    MessTmr: TTimer;
    TextColorBtn: TMenuItem;
    BlackBtn: TMenuItem;
    WhiteBtn: TMenuItem;
    GreenBtn: TMenuItem;
    BlueBtn: TMenuItem;
    FuchsiaBtn: TMenuItem;
    ImageList1: TImageList;
    Panel2: TPanel;
    Panel3: TPanel;
    Label15: TLabel;
    Label18: TLabel;
    Image1: TImage;
    Label21: TLabel;
    Label1: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label25: TLabel;
    Panel1: TPanel;
    Panel4: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Button1: TButton;
    Label6: TLabel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    N1: TMenuItem;
    AlarmEnableBtn: TMenuItem;
    N10001: TMenuItem;
    Label7: TLabel;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    Timer1: TTimer;
    PortSub: TMenuItem;
    COM11: TMenuItem;
    COM21: TMenuItem;
    COM31: TMenuItem;
    COM41: TMenuItem;
    COM51: TMenuItem;
    Voltage: TLabel;
    Load_stat_btn: TButton;
    Image2: TImage;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Timer2: TTimer;
    Timer3: TTimer;
    ComboBox1: TComboBox;
    Button2: TButton;
    SavePictureDialog1: TSavePictureDialog;
    IdHTTP1: TIdHTTP;
    Timer4: TTimer;
    RUSENG1: TMenuItem;
    Button3: TButton;
    SaveDialog1: TSaveDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ExitBtnClick(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
    procedure AutoStartupBtnClick(Sender: TObject);
    procedure MessTmrTimer(Sender: TObject);
    procedure BlackBtnClick(Sender: TObject);
    procedure WhiteBtnClick(Sender: TObject);
    procedure GreenBtnClick(Sender: TObject);
    procedure BlueBtnClick(Sender: TObject);
    procedure FuchsiaBtnClick(Sender: TObject);
    procedure RedBtnClick(Sender: TObject);
    procedure YellowBtnClick(Sender: TObject);
    procedure SilverBtnClick(Sender: TObject);
    procedure AquaBtnClick(Sender: TObject);
    procedure OliveBtnClick(Sender: TObject);
    procedure MyTrayDoubleClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure MyTrayClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button1Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure AboutBtnClick(Sender: TObject);
    procedure AlarmEnableBtnClick(Sender: TObject);
    procedure N10001Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure COM11Click(Sender: TObject);
    procedure COM21Click(Sender: TObject);
    procedure COM31Click(Sender: TObject);
    procedure COM41Click(Sender: TObject);
    procedure COM51Click(Sender: TObject);
    procedure Load_stat_btnClick(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure Draw_massive();
    procedure Timer3Timer(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Image2Click(Sender: TObject);
    procedure Timer4Timer(Sender: TObject);
    procedure RUSENG1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
     private
    { Private declarations }
    RS232: TiaRS232;
    fBuf: TiaBuf;
    fBufCount: Integer;
    procedure DoOnReceiveEvent(Sender: TObject; Const aData: TiaBuf;
      aCount: Cardinal);
    procedure DoOnSendedEvent(Sender: TObject; Const aData: TiaBuf;
      aCount: Cardinal);
 protected
  public
    procedure RefreshRAD;
    procedure SaveReg;
    procedure MakeIcon(f_fon: ulong);
    procedure WMPowerBroadcast(var MyMessage: TMessage); message WM_POWERBROADCAST;
end;

var
  mainFrm: TmainFrm;
  FeatureReportLen: integer = 0;
  DevPresent: boolean = false;
  DenyCommunications: boolean = false;
  pingback: integer;
  AutoStartup: boolean = true;
  AlarmEnable: boolean = true;
  alarmlevel: ulong = 40;
  needexit: boolean = false;
  tempcol: TColor = clLime;
  Fon_units: string;
  bmp:TBitmap;
  png: TPNGObject;
  count_validate_percent: uint;
  IMPS: uint = 0;
  Fon: ulong = 0;
  count_validate: uchar = 0;
  count_interval: uchar = 0;
  blinker: boolean;
  impps: array[0..61] of uint;
  fonps: array[0..61] of ulong;
  fonpermin: array[0..61] of ulong;
  divgraphminute: ulong =1;
  fonperhour: array[0..25] of ulong;
  divgraphhour: ulong =1;
  fonpm: ulong;
  fonpmm: ulong;
  divgraphimp: uint = 3;
  dosefull: ulong;
  doseday: ulong;
  doseadd: ulong;
  i: uchar;
  temperature: uchar;
  tempsign: boolean;
  divgraph: ulong =6;
  graph_x: uint;
  graph_y: uint;
  graph_y2: uint;
  g_color: uint;
  d_second: uchar = 0;
  d_minute: uchar = 0;
  d_hour: uchar = 0;
  d_day: ulong = 0;
  maxfon: ulong = 0;
  serial_active:  boolean = false;
  comport_number: uint = 1;
  USB_massive_loading: boolean = false;
  max_fon_massive: array[0..10080] of UInt32;
  doze_massive: array[0..10080] of UInt32;
  selected_point_massive: uint;

  max_fon_massive_ready: array[0..10080] of boolean;
  doze_massive_ready: array[0..10080] of boolean;

  geiger_seconds_count: uint32 = 1;
  address: UInt32 = 0;
  address_last: UInt32 = 0;
  doze_loading_flag:  boolean = false;
  maxfon_loading_flag:  boolean = false;
  lang_settings:  boolean = false;
  usb_send_try: UInt32 = 0;
  Fix_error_now: boolean = false;
  time_offset:uint32;
  myDate : TDateTime;
  formattedDateTime : string;


mr_lang: string =        '��/�';
mkr_lang: string =       ' ���';
mkr2_lang: string =      ' ���/�';
mkr3_lang: string =      '���/�]';
dos_off_lang: string =   '�������� �� ���������';
normal_lang: string =    '[ ���������� ��� ]';
high_lang: string =      '[ ���������� ��� ]';
danger_lang: string =    '[ ������� ��� ]';
imps_lang: string =      '���.';
ZA_lang: string =        '�� ';
day_lang: string =       ' ���� ';
hour_lang: string =      ' ����� ';
minute_lang: string =    ' �����,';
summary_lang: string =   '��������� ����: ';
maxi_lang: string =      '������������ ��� �� ��� �����: ';
error_lang: string =     '������:';
curr_lang: string =      '������� ���:';
alarm_lang: string =     '������� [';
dosi_name_lang: string = '������-������ ';
avg_lang: string =       '������� ��� ';
maxi2_lang: string =     '������������ ��� ';
avg2_lang: string =      '������� ��� 0 ���/�';
maxi3_lang: string =     '������������ ��� 0 ���/�';
time_lang: string =      '����� ';
hours2_lang: string =    ' ���(��)   ';
minutes2_lang: string =  ' �����';
alarm2_lang: string =    '�������!';
fonmax_lang: string =    '��� ����� ';
voltage_lang: string =   '���������� ���: ';
loading_lang: string =   '��������...';


implementation

{$R *.dfm}
{$R sounds.res}
uses Unit1;

procedure TmainFrm.WMPowerBroadcast(var MyMessage: TMessage);
begin
if MyMessage.Msg = WM_POWERBROADCAST then begin
if MyMessage.WParam = PBT_APMRESUMEAUTOMATIC then begin
    DenyCommunications:= false;
end
else begin
    DevPresent:= false;
    DenyCommunications:= true;
    RS232.StopListner;
    RS232.Close;
end;
end;
inherited;
end;


procedure TmainFrm.SaveReg;
var
  reg: TRegistry;
begin
  reg := TRegistry.Create;                               // ��������� ������
  reg.RootKey := HKEY_CURRENT_USER;                      // ��� �������� ������������
  reg.OpenKey('Software\USB_Geiger\USB_Geiger', true); // ��������� ������
  reg.WriteBool('autorun', AutoStartup);
  reg.WriteBool('alarmenable', AlarmEnable);
  reg.WriteBool('lang', lang_settings);
  reg.WriteInteger('alarmlevel', AlarmLevel);
  reg.WriteInteger('comport',comport_number);
  reg.CloseKey;                                          // ��������� ������
  reg.OpenKey('Software\Microsoft\Windows\CurrentVersion\Run', true);  // ��������� ������
  if AutoStartup then
    reg.WriteString('USB_Geiger', application.ExeName)       // ����������
  else
    reg.DeleteValue('USB_Geiger');                          // ��� ������� ����������
  reg.CloseKey;                                          // ��������� ������
  reg.Free;
end;




procedure TmainFrm.MakeIcon(f_fon: ulong);
var
 ii: uint;
begin

  if (not DevPresent) then
    begin
  ImageList1.GetIcon(0,MyTray.Icon);
  MyTray.Hint := dos_off_lang;
    end
    else
    begin


  MyTray.Hint := 'USB Geiger: '+IntToStr(Fon)+' '+fon_units;

      if ((count_validate >0) and blinker) then
      begin
        ImageList1.GetIcon(1,MyTray.Icon);
        blinker := false;
      end
      else
      begin // cv
        blinker:=true;
        if (Fon < 41) and (Fon_units <> mr_lang) then
        begin
          Panel1.Color := clGreen;
          Label7.Caption := normal_lang;
          ImageList1.GetIcon(2,MyTray.Icon);
        end
        else if (Fon < 121) and (Fon_units <> mr_lang) then
        begin
          Panel1.Color := clOlive;
          Label7.Caption := high_lang;
          ImageList1.GetIcon(3,MyTray.Icon);
        end
        else
        begin
          Panel1.Color := clMaroon;
          Label7.Caption := danger_lang;
          ImageList1.GetIcon(4,MyTray.Icon);
        end;
      end; // cv
    end;

  Image1.Canvas.Brush.Color := clWhite;
  Image1.Canvas.Pen.Color := clWhite;
  Image1.Canvas.Rectangle(4, 0,305,100);
  Image1.Canvas.Pen.Color := clBlack;
  Image1.Canvas.Rectangle(2, 0,3,100);
  Image1.Canvas.Rectangle(0, 98,305,97);

  if RadioButton1.Checked then
begin
// ���� ���������
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (impps[ii]>5) then g_color:=clRED
    else if (impps[ii]>3) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((impps[ii]*95) div divgraphimp)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;

      Fon_units := imps_lang;
    Label22.Caption := IntToStr(divgraphimp);
    Label23.Caption := fon_units;
// ���� ���������
end
else if RadioButton2.Checked then
begin
  // ���� ���� ���
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonps[ii]>120) then g_color:=clRED
    else if (fonps[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonps[ii]*95) div divgraph)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;
    begin
      Fon_units := mkr2_lang;
    end;
    Label22.Caption := IntToStr(divgraph);
    Label23.Caption := fon_units;
// ���� ���� ���
end
else if RadioButton3.Checked then
begin
  // ���� ���� ���
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonpermin[ii]>120) then g_color:=clRED
    else if (fonpermin[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonpermin[ii]*95) div divgraphminute)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;
    begin
      Fon_units := mkr2_lang;
    end;
    Label22.Caption := IntToStr(divgraphminute);
    Label23.Caption := fon_units;
// ���� ���� ���
end
else if RadioButton4.Checked then
begin
  // ���� ���� ���
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonperhour[ii]>120) then g_color:=clRED
    else if (fonperhour[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonperhour[ii]*95) div divgraphhour)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+9, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+12;
    end;
    begin
      Fon_units := mkr2_lang;
    end;
    Label22.Caption := IntToStr(divgraphhour);
    Label23.Caption := fon_units;
// ���� ���� ���
end;

// ���� �����    Label3.Caption := '[������] - ��������� � �������: '+IntToStr(IMPS);
    Label4.Caption := ZA_lang+IntToStr(d_day)+day_lang+IntToStr(d_hour)+hour_lang+IntToStr(d_minute)+minute_lang;

    if (d_minute > 0) then
    begin
      doseadd := (fonpmm div 60);
    end else doseadd := 0;
    begin
    Label5.Caption := summary_lang+IntToStr(dosefull+doseday+doseadd)+mkr_lang;
    end;
      Label6.Caption := maxi_lang+IntToStr(maxfon)+mkr2_lang;
end;

procedure TmainFrm.RefreshRAD;
begin
    MakeIcon(Fon);
end;

procedure TmainFrm.RUSENG1Click(Sender: TObject);
begin
lang_settings:=RUSENG1.Checked;
SaveReg;
end;

procedure TmainFrm.FormCreate(Sender: TObject);
var
  reg: TRegistry;
begin

  Image2.Canvas.Brush.Color := RGB(186, 170, 134);
  Image2.Canvas.Pen.Color := clBlack;
  Image2.Canvas.Rectangle(0,0,Image2.Width, Image2.Height);
  MainFrm.Width:=400;
  RS232 := TiaRS232.Create;
  RS232.OnRSReceived := DoOnReceiveEvent;
  RS232.OnRSSended := DoOnSendedEvent;
  SetLength(fBuf, 64);
  fBufCount := 0;

  //Setting the default value

  MyTray.IconIndex := -1;
  MessTmr.Enabled := true;
  reg := TRegistry.Create;                              // ��������� ������
  reg.RootKey := HKEY_CURRENT_USER;
  if reg.OpenKey('Software\USB_Geiger\USB_Geiger', false) then
  begin
    try
      AutoStartup := reg.ReadBool('autorun');
    except
      AutoStartup := false;
    end;
    try
      lang_settings := reg.ReadBool('lang');
    except
      lang_settings := false;
    end;
    try
      comport_number := reg.ReadInteger('comport');
    except
      comport_number := 1;
    end;
    try
      AlarmEnable := reg.ReadBool('alarmenable');
    except
      AlarmEnable := false;
    end;
    try
      AlarmLevel := reg.ReadInteger('alarmlevel');
    except
      AlarmLevel := 40;
    end;
  end else begin    // ���� ��� ������� -> ����� ��� �� ����������� -> ������ �� ������������
    reg.OpenKey('Software\USB_Geiger\USB_Geiger', true);
    AutoStartup := true;
    try
      reg.WriteBool('autorun', AutoStartup);
    except
    end;
    try
      reg.WriteInteger('comport', 1);
    except
    end;

    try
      reg.WriteBool('alarmenable', AlarmEnable);
    except
    end;
    try
      reg.WriteInteger('alarmlevel', AlarmLevel);
    except
    end;
    reg.CloseKey;                                          // ��������� ������
    try
      reg.OpenKey('Software\Microsoft\Windows\CurrentVersion\Run', true); // ��������� ������
      reg.WriteString('USB_Geiger', application.ExeName)       // ����������
    except
    end;
  end;
  reg.CloseKey;                                        // ��������� ������
  reg.Free;
  AutoStartupBtn.Checked := AutoStartup;
  RUSENG1.Checked := lang_settings;
  AlarmEnableBtn.Checked := AlarmEnable;
  if(comport_number=1)then COM11.Checked := true;
  if(comport_number=2)then COM21.Checked := true;
  if(comport_number=3)then COM31.Checked := true;
  if(comport_number=4)then COM41.Checked := true;
  if(comport_number=5)then COM51.Checked := true;

  if (lang_settings=false) then
  begin

    mr_lang:=        'mR/h';
    mkr_lang:=       ' uR';
    mkr2_lang:=      ' uR/h';
    mkr3_lang:=      'uR/h]';
    dos_off_lang:=   'Dosimeter not connected';
    normal_lang:=    '[ normal radiation level ]';
    high_lang:=      '[ high radiation level ]';
    danger_lang:=    '[ !!! DANGER !!! ]';
    imps_lang:=     'Imp.';
    ZA_lang:=        'On ';
    day_lang:=       ' days ';
    hour_lang:=      ' hours ';
    minute_lang:=    ' minute,';
    summary_lang:=   'Summary dose: ';
    maxi_lang:=      'Maximum peak radiation level: ';
    error_lang:=     'Error:';
    curr_lang:=      'radiation level:';
    alarm_lang:=     'ALARM [';
    dosi_name_lang:= 'Ultra-Micron ';
    avg_lang:=       'Avg level ';
    maxi2_lang:=     'Max level ';
    avg2_lang:=      'Avg level 0 uR/h';
    maxi3_lang:=     'Max level 0 uR/h';
    time_lang:=      'Time ';
    hours2_lang:=    ' hours   ';
    minutes2_lang:=  ' minute';
    alarm2_lang:=    'ALARM!';
    fonmax_lang:=    'radiation level up to ';
    voltage_lang:=   'Li-Ion voltage: ';

    Label7.Caption:=       '';
    Label18.Caption:=       '';
    Label2.Caption:=       'Accumulated radiation dose:';
    Load_stat_btn.Caption:='Load logs';
    OKBtn.Caption:=        'Hide';
    Button1.Caption:=      'Clear';
    Button2.Caption:=      'Screenshot';
    Button3.Caption:=      'Save to CSV';
    Radiobutton4.Caption:= 'dose/h';
    Radiobutton3.Caption:= 'dose/m';
    Radiobutton2.Caption:= 'dose/s';
    Radiobutton1.Caption:= 'imp/10s';

    N1.Caption:='Dosimeter';
    TextColorBtn.Caption:='Alarm level';
    PortSub.Caption:='COM Port';
    AlarmEnableBtn.Caption:='Enable Alarm';
    AboutBtn.Caption:='About';
    ExitBtn.Caption:='Exit';
    AutoStartupBtn.Caption:='Autostart';

    BlackBtn.Caption:='25 uR/h';
    WhiteBtn.Caption:='40 uR/h';
    GreenBtn.Caption:='120 uR/h';
    BlueBtn.Caption:='400 uR/h';
    FuchsiaBtn.Caption:='1000 uR/h';
    N10001.Caption:='3000 uR/h';
    loading_lang:='Loading...';

  end

end;


procedure TmainFrm.COM11Click(Sender: TObject);
begin
comport_number:=1;
SaveReg;
COM11.Checked := true;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := false;
end;

procedure TmainFrm.COM21Click(Sender: TObject);
begin
comport_number:=2;
SaveReg;
COM11.Checked := false;
COM21.Checked := true;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := false;
end;

procedure TmainFrm.COM31Click(Sender: TObject);
begin
comport_number:=3;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := true;
COM41.Checked := false;
COM51.Checked := false;
end;

procedure TmainFrm.COM41Click(Sender: TObject);
begin
comport_number:=4;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := true;
COM51.Checked := false;
end;

procedure TmainFrm.COM51Click(Sender: TObject);
begin
comport_number:=5;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := true;
end;


procedure TmainFrm.ComboBox1Change(Sender: TObject);
begin
  Draw_massive();
end;

procedure TmainFrm.ExitBtnClick(Sender: TObject);
begin
  if(DevPresent=true) then
   begin
      DevPresent:=false;
   end;

  needexit := true; // ������� ������ ������� �� ������
end;

procedure TmainFrm.OKBtnClick(Sender: TObject);
begin
  MainFrm.Width:=400;
  Timer2.Enabled:=false;
  MyTray.HideApplication;
end;

procedure TmainFrm.AutoStartupBtnClick(Sender: TObject);
begin
  AutoStartup := AutoStartupBtn.Checked;
  SaveReg;
end;

procedure TmainFrm.MessTmrTimer(Sender: TObject);
var
iz: uchar;
begin
  RefreshRAD;
  // ������
  fonpm := fonpm+fonps[d_second];
  d_second:=d_second+1;
  if(d_second = 60)then
  begin
  d_second:=0;
    fonpmm := fonpmm + (fonpm div 60);


    fonpermin[0] := fonpm div 60;
    divgraphminute := 1;
    for iz := 60 downto 1 do
    begin
    fonpermin[iz] := fonpermin[iz-1];
    if fonpermin[iz] > divgraphminute then divgraphminute := fonpermin[iz];
    end;
    fonpermin[0] := 0;


    fonpm := 0;
  d_minute:=d_minute+1;
      if (d_minute = 60) then
      begin

    fonperhour[0] := fonpmm div 60;
    divgraphhour := 1;
    for iz := 24 downto 1 do
    begin
    fonperhour[iz] := fonperhour[iz-1];
    if fonperhour[iz] > divgraphhour then divgraphhour := fonperhour[iz];
    end;
    fonperhour[0] := 0;

      d_minute:=0;
      doseday:= doseday + (fonpmm div 60);
      fonpmm := 0;
      d_hour:=d_hour+1;
          if (d_hour=24) then
          begin
          d_hour:=0;
          d_day:=d_day+1;
          dosefull := dosefull + doseday;
          doseday:=0;
          end;
      end;
  end;
  // ������
    if needexit then
    application.Terminate;
end;

procedure TmainFrm.MyTrayClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
if Button <> mbRight then
begin
  if (not DevPresent) then
      MyTray.BalloonHint(error_lang,dos_off_lang,TBalloonType(3),5000,true)
    else
      MyTray.BalloonHint(curr_lang,IntToStr(Fon)+' '+fon_units,TBalloonType(2),5000,true);
end;
      AlarmEnableBtn.Caption := alarm_lang+IntToStr(alarmlevel)+mkr3_lang;
end;

procedure TmainFrm.N10001Click(Sender: TObject);
begin
   alarmlevel:=3000;
  SaveReg;
end;

procedure TmainFrm.MyTrayDoubleClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  MyTray.ShowApplication;
end;

procedure TmainFrm.N1Click(Sender: TObject);
begin
  MyTray.ShowApplication;
end;

procedure TmainFrm.AlarmEnableBtnClick(Sender: TObject);
begin
  AlarmEnable := AlarmEnableBtn.Checked;
  SaveReg;
end;

procedure TmainFrm.BlackBtnClick(Sender: TObject);
begin
  alarmlevel:=25;
  SaveReg;
end;

procedure TmainFrm.WhiteBtnClick(Sender: TObject);
begin
  alarmlevel:=40;
  SaveReg;
end;

procedure TmainFrm.GreenBtnClick(Sender: TObject);
begin
    alarmlevel:=120;
  SaveReg;
end;


procedure TmainFrm.Image2Click(Sender: TObject);
var
  foo: TPoint;
begin

if selected_point_massive = 0 then
begin
  Timer2.Enabled := False;
  foo:=Image2.ScreenToClient(Mouse.CursorPos);
  selected_point_massive:=((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset;
  Draw_massive();
end
else
begin
   selected_point_massive :=0;
   Timer2.Enabled := True;
   Draw_massive();
end;

end;


procedure TmainFrm.Load_stat_btnClick(Sender: TObject);
var
  vAns: TiaBuf;
  ix: uint;
  ibx: uint;
begin

Unit1.Form1.Show;

  myDate:=Now;

  if (lang_settings=false) then
  begin
    Unit1.Form1.Label5.Caption:='Dont stop the process. Dont turn off device!';
    Unit1.Form1.Label1.Caption:='Loading maximum radiation array:';
    Unit1.Form1.Label2.Caption:='Loading average radiation array:';
    Unit1.Form1.Label4.Caption:='Loading to web service:';
  end;


Unit1.Form1.max_fon.Caption:='0%';
Unit1.Form1.impulses.Caption:='0%';
Unit1.Form1.errors.Caption:='0';
RS232.StopListner;
RS232.Close;
Timer2.Enabled:=true;
doze_loading_flag:= false;
maxfon_loading_flag:=false;
address_last:=8640;

ComboBox1.Items.Clear;
for ibx := 0 to 60 do
begin
Combobox1.AddItem(DateToStr(Date-ibx), nil);
end;

Combobox1.ItemIndex := 0;


DateTimeToString(formattedDateTime, 'h', Now);
time_offset:=StrToInt(formattedDateTime)*60;
DateTimeToString(formattedDateTime, 'n', Now);
time_offset:=time_offset+StrToInt(formattedDateTime);
time_offset:=144-(time_offset Div 10); //113

if (RS232.Active = false) then
begin
  DevPresent:=false;
  RS232.Properties.PortNum  := comport_number;
  RS232.Properties.BaudRate := CBR_115200;
  RS232.Properties.Parity   := NOPARITY;
  RS232.Properties.StopBits := ONESTOPBIT;
  RS232.Open;
  RS232.StartListner;
  for ix := 0 to 8640 do begin
    doze_massive[ix]:=0;
    max_fon_massive[ix]:=0;
    doze_massive_ready[ix]:=false;
    max_fon_massive_ready[ix]:=false;
  end;

  if (RS232.Active)then
  begin
   DevPresent:=true;

   SetLength(vAns, 1);
   vAns[0]:=$39; // ��������� ����� ��������� ���������
   RS232.Send(vAns);

   SetLength(vAns, 1);
   vAns[0]:=$33; // ������� ���������
   RS232.Send(vAns);

   SetLength(vAns, 1);
   vAns[0]:=$39; // ��������� ����� ��������� ���������
   RS232.Send(vAns);


   SetLength(vAns, 1);
   vAns[0]:=$31; // ������ �������� �������
   maxfon_loading_flag:=true;
   RS232.Send(vAns);
   sleep(1);
   USB_massive_loading:=true;


  end
  else
    Unit1.Form1.Close;
    Fix_error_now:=false;
  end;
end;


procedure TmainFrm.BlueBtnClick(Sender: TObject);
begin
    alarmlevel:=400;
  SaveReg;
end;

procedure TmainFrm.Button1Click(Sender: TObject);
var im:uchar;
begin
dosefull:=0;
doseday:=0;
d_day:=0;
d_hour:=0;
d_minute:=0;
d_second:=0;
maxfon:=0;
fonpmm:=0;
for im := 0 to 61 do fonpermin[im] := 0;
for im := 0 to 25 do fonperhour[im] :=0;

end;



procedure TmainFrm.Button2Click(Sender: TObject);
begin
 bmp := TBitmap.Create;
 bmp.Width := mainFrm.Width-10;
 bmp.Height := mainFrm.Height-30;
 BitBlt(bmp.Canvas.Handle, 0,0, mainFrm.Width-10, mainFrm.Height-30, GetDC(mainFrm.Handle), 0,0,SRCCOPY);

png := TPNGObject.create;
png.assign(bmp);


SavePictureDialog1.DefaultExt := '.png';
SavePictureDialog1.FileName := dosi_name_lang+Combobox1.Text+'.png';

If SavePictureDialog1.Execute then
   begin
     png.SaveToFile(SavePictureDialog1.fileName);
   end;
bmp.Free;
png.free;

end;

procedure TmainFrm.Button3Click(Sender: TObject);
var
  F: TextFile;
  FileName: string;
  I: Integer;
  ix: Integer;
  TempStr: string;
  Y, M, D: Word;
begin
  SaveDialog1.DefaultExt := '.csv';
  SaveDialog1.FileName := dosi_name_lang+'.csv';

  If SaveDialog1.Execute then
   begin
   try
    AssignFile(F, SaveDialog1.fileName);  // ������� ���� � ����������
    Rewrite(F);               // ������� ������ ����
// ���� ������ � ���������� �� �����, �� ����� ��� ������ �������.

    WriteLn(F,
        '"', 'Element', '";',
        '"', 'Timestamp', '";',
        '"', 'Avg_Fon', '";',
        '"', 'Max_Fon', '"');

    for ix := 0 to 8640 do begin
     if doze_massive[ix]>0 then begin
       DateTimeToString(formattedDateTime, 'c', IncMinute(myDate, -(10*ix)));
       WriteLn(F,
          '"', IntToStr(ix), '";',
          '"', formattedDateTime,      '";',
          '"', IntToStr((doze_massive[ix] * geiger_seconds_count) Div 600), '";',
          '"', IntToStr(max_fon_massive[ix]), '"');
       end;
    end;
  finally
    CloseFile(F);
  end;
 end;
end;

procedure TmainFrm.FuchsiaBtnClick(Sender: TObject);
begin
    alarmlevel:=1000;
  SaveReg;
end;

procedure TmainFrm.RedBtnClick(Sender: TObject);
begin
  tempcol := clRed;
  SaveReg;
end;

procedure TmainFrm.YellowBtnClick(Sender: TObject);
begin
  tempcol := clYellow;
  SaveReg;
end;

procedure TmainFrm.SilverBtnClick(Sender: TObject);
begin
  tempcol := clSilver;
  SaveReg;
end;

procedure TmainFrm.Timer1Timer(Sender: TObject);
var
  vAns: TiaBuf;
begin
if(DenyCommunications = false) then begin
if(USB_massive_loading = false) then begin
  if (RS232.Active = false) then
  begin
    RS232.Properties.PortNum  := comport_number;
    RS232.Properties.BaudRate := CBR_115200;
    RS232.Properties.Parity   := NOPARITY;
    RS232.Properties.StopBits := ONESTOPBIT;
    RS232.Open;
    RS232.StartListner;

    if (RS232.Active)then
    begin
     DevPresent:=true;
     SetLength(vAns, 1);
     vAns[0]:=$d4;
     RS232.Send(vAns);
    end
    else
    begin
      if(DevPresent=true) then
      begin
        DevPresent:=false;
      end;
      RS232.StopListner;
      RS232.Close;
    end;
  end
  else
  begin
      RS232.StopListner;
      RS232.Close;
  end;
end;
end;
end;

procedure TmainFrm.Timer2Timer(Sender: TObject);
var
  foo: TPoint;
  tick: uint32;
  hour: uint32;
  minute: uint32;
begin
  foo:=Image2.ScreenToClient(Mouse.CursorPos);
  if(foo.X < Image2.Width) and (foo.Y < Image2.Height) and (foo.X > 0) and (foo.Y > 0) then
  begin
    tick:=((foo.X+3) Div 5);
    while tick>0 do
    begin
      if (tick >= 6) then
      begin
       hour:=hour+1;
       tick:=tick-6;
      end
      else
      begin
       minute:=tick*10;
       tick:=0;
      end;
    end;

    if ((((Image2.Width-foo.X) Div 5)>time_offset) or (Combobox1.ItemIndex <> 0)) then begin
      Label9.Caption:=avg_lang+    IntToStr(((doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset] * geiger_seconds_count) Div 600))+   mkr2_lang;
      Label10.Caption:=maxi2_lang+IntToStr(max_fon_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset])+mkr2_lang;
    end else begin
      Label9.Caption:=avg2_lang;
      Label10.Caption:=maxi3_lang;
    end;
    Label11.Caption:=time_lang+IntToStr(hour)+hours2_lang+IntToStr(minute)+minutes2_lang;

end;
end;

procedure TmainFrm.Timer3Timer(Sender: TObject);
var
  vAns: TiaBuf;
  iy: uint32;
begin

if(usb_send_try < 100) then
 begin
   if (address = address_last) and (USB_massive_loading = true) then
   begin
    SetLength(vAns, 1);
    usb_send_try:=usb_send_try+1;
    if(Fix_error_now = false) then Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)+1);
    if(doze_loading_flag = true) then vAns[0]:=$32;
    if(maxfon_loading_flag=true) then vAns[0]:=$31;
    RS232.Send(vAns);
   end
   else address_last:=address;
  end
  else
  begin
    address:=0;
    address_last:=0;
    usb_send_try:=0;
    RS232.StopListner;
    RS232.Close;
    Unit1.Form1.Close;
    Fix_error_now:=false;
    Load_stat_btn.Caption:='������ ������';
    USB_massive_loading:=false;
    doze_loading_flag:=false;
    maxfon_loading_flag:=false;

  end;
end;

procedure TmainFrm.Timer4Timer(Sender: TObject);
var
 AIdHTTP: TIdHTTP;
 reg: TRegistry;
 key: String;
begin
if (DevPresent) then
  begin
    reg := TRegistry.Create;                              // ��������� ������
    reg.RootKey := HKEY_CURRENT_USER;
    reg.OpenKey('Software\USB_Geiger\USB_Geiger', false);
    key := reg.ReadString('Reg_key');
    reg.CloseKey;                                          // ��������� ������
    AIdHTTP := TIdHTTP.Create(nil);
    AIdHTTP.HandleRedirects := true;
    try
      AIdHTTP.Get(  Concat('http://upload.xn--h1aeegel.net/upload.php?id=',key,'&fon=',IntToStr(fon)));
    except
      begin
      end;
    end;
    AIdHTTP.Disconnect;
    AIdHTTP.Free;
  end;
end;

procedure TmainFrm.AboutBtnClick(Sender: TObject);
begin
try
About.ShowModal;
except
end;
end;

procedure TmainFrm.AquaBtnClick(Sender: TObject);
begin
  tempcol := clAqua;
  SaveReg;
end;

procedure TmainFrm.OliveBtnClick(Sender: TObject);
begin
  tempcol := clOlive;
  SaveReg;
end;



procedure TmainFrm.FormDestroy(Sender: TObject);
begin
  RS232.StopListner;
  FreeAndNil(RS232);
end;

procedure TmainFrm.Draw_massive();
var
 ii: uint32;
 scale_factor: uint32;
 always_multipiller: uint32;
 massive_pointer:uint32;
begin
// ���� ���������

MainFrm.Width:=1148;
  Image2.Picture:= nil;

  Image2.Canvas.Brush.Color := RGB(186, 170, 134);
  Image2.Canvas.Pen.Color := clBlack;
  Image2.Canvas.Rectangle(0,0,Image2.Width, Image2.Height);

  graph_x:=0;
  graph_y:=96;
  always_multipiller:=Image2.Height Div 5;
  scale_factor:=10;

    for ii := 0 to 144 do
    begin
      if ((ii>time_offset) or (Combobox1.ItemIndex <> 0)) then begin
        if((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller)>=Image2.Height) then
        begin
          if(scale_factor < (((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller) Div Image2.Height)+1)) then
          scale_factor:=((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller) Div Image2.Height)+1;

          if(scale_factor = 0) then scale_factor:=1;
        end;
      end;

    end;

    for ii := 0 to 144 do
    begin
      if ((ii>time_offset) or (Combobox1.ItemIndex <> 0)) then begin

        graph_y:= (max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]                                    * always_multipiller) Div scale_factor;
        graph_y2:=((( doze_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]  * geiger_seconds_count) Div 600)  * always_multipiller) Div scale_factor;

        if graph_y=graph_y2 then graph_y2:=graph_y-1;
        Image2.Canvas.Brush.Color :=  RGB(0, 29, 135);
        if (selected_point_massive = ii+(144*(Combobox1.ItemIndex))-time_offset) then Image2.Canvas.Brush.Color :=  RGB(255, 0, 0);
        Image2.Canvas.Brush.Style:= bsSolid;
        Image2.Canvas.Pen.Color := clBlack;
        Image2.Canvas.Rectangle(Image2.Width-graph_x-4, Image2.Height, Image2.Width-graph_x, Image2.Height-graph_y2);

        Image2.Canvas.Brush.Color := clRED;
        Image2.Canvas.Brush.Style:= bsBDiagonal;
        if (selected_point_massive = ii+(144*(Combobox1.ItemIndex))-time_offset) then  Image2.Canvas.Brush.Style:= bsDiagCross;
        Image2.Canvas.Pen.Color := clBlack;
        Image2.Canvas.Rectangle(Image2.Width-graph_x-4, Image2.Height-graph_y2, Image2.Width-graph_x, Image2.Height-graph_y);
      end;
      graph_x:=graph_x+5;
    end;

    graph_y:= (15 * always_multipiller) Div scale_factor; // ����� 15 ���/�
    Image2.Canvas.Brush.Color := clGREEN;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clGREEN;
    Image2.Canvas.Font.Color:=clGREEN;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      Image2.Canvas.TextOut(0,Image2.Height-graph_y,'15'+mkr2_lang);
    end;

    graph_y:= (30 * always_multipiller) Div scale_factor; // ����� 30 ���/�
    Image2.Canvas.Brush.Color := clYELLOW;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clYELLOW;
    Image2.Canvas.Font.Color:=clYELLOW;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      Image2.Canvas.TextOut(0,Image2.Height-graph_y,'30'+mkr2_lang);
    end;

    graph_y:= (50 * always_multipiller) Div scale_factor; // ����� 50 ���/�
    Image2.Canvas.Brush.Color := clRED;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clRED;
    Image2.Canvas.Font.Color:=clRED;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      Image2.Canvas.TextOut(0,Image2.Height-graph_y,'50'+mkr2_lang);
    end;

end;



//================================================================================================================
procedure TmainFrm.DoOnReceiveEvent(Sender: TObject; const aData: TiaBuf; aCount: Cardinal);
Var
  ia:uint;
  F: Integer;
  ss: String;
  vCount: Integer;
  vBufCount: Integer;
  Voltage_level: Integer;
  massive_element: UInt32 ;
  vAns: TiaBuf;
  ix : uint32;
  iy : uint32;
  buffer_len: uint32;
  used_len: uint32;
  packet_size: uint32;
  aData_massive_pointer: uint32;
  fBuf_pointer: uint32;
  StopRS232: Boolean;
  AIdHTTP: TIdHTTP;
  reg: TRegistry;
  key: String;
  data: TIdMultiPartFormDataStream;


begin
Voltage_level:=0;
packet_size:=7;
aData_massive_pointer:=0;
fBuf_pointer:=0;
StopRS232:=FALSE;

While used_len<(Length(aData)-1) do begin

  // ���������� ������� ������
   For F := aData_massive_pointer to aData_massive_pointer + packet_size - 1 do
     Begin
       fBuf[fBuf_pointer] := aData[F];
       Inc(fBuf_pointer);
       if F > (Length(aData)-1) then Break;
       used_len:=F;
     end;
   aData_massive_pointer:=used_len+1;
   fBuf_pointer:=0;

     begin
       ss := '';
       For F := 0 To packet_size - 1 do
         ss := ss + IntToHex(fBuf[F],2) + ' ';

//-----------------------------------------------------------------------------------
if (fBuf[0] = $d1) then begin
  Fon :=0;
  IMPS :=0;

  count_validate := 0;
  count_interval := 0;
  IMPS := (fBuf[1] shl 8)+fBuf[2]; // �������� 2 ����
  Fon := ((fBuf[3] shl 16)+(fBuf[4] shl 8))+fBuf[5]; // �������� 3 ����
  Voltage_level := (fBuf[6]+300) *10; // �������� 2 ����
  count_validate := 0;
  count_interval := 30;

  // ���������� �������
  if (alarmenable and (fon > alarmlevel) and (d_minute mod 2 = 0) and (d_second mod 10 = 0)) then
  begin
    MyTray.BalloonHint(alarm2_lang,fonmax_lang+IntToStr(alarmlevel)+mkr2_lang,TBalloonType(3),5000,true);
    PlaySound('alarm', hInstance, SND_RESOURCE);
  end;

  // ���������� �������
  if maxfon < fon then maxfon:=fon;

  // ��������� ������� ���������
  impps[0] := IMPS;
  divgraphimp := 3;
  for ia := 60 downto 1 do //?
  begin
    impps[ia] := impps[ia-1];
    if impps[ia] > divgraphimp then divgraphimp := impps[ia];
  end;
  impps[0] := 0;

  // ��������� ������� ����
  fonps[0] := fon;
  divgraph := 6;
  for ia := 61 downto 1 do
  begin
    fonps[ia] := fonps[ia-1];
    if fonps[ia] > divgraph then divgraph := fonps[ia];
  end;
  fonps[0] := 0;
  Fon_units := mkr2_lang;

  Label15.Caption := IntToStr(fon);
  Label18.Caption := fon_units;

  if count_interval >0 then count_validate_percent := (100*(count_interval-count_validate)) div count_interval;

  SetLength(vAns, 1);
  if(doze_loading_flag = true) then vAns[0]:=$32;
  if(maxfon_loading_flag=true) then vAns[0]:=$31;

StopRS232:= TRUE;
end;
//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
if ((fBuf[0] = $f1) or (fBuf[0] = $81))  then begin // �������� �������� ������� ������������� ����

  address:=         fBuf[1] shl 8;
  address:=address+ fBuf[2];

  massive_element:=                 fBuf[3] shl 24;
  massive_element:=massive_element+(fBuf[4] shl 16);
  massive_element:=massive_element+(fBuf[5] shl 8);
  massive_element:=massive_element+ fBuf[6];

  if (address < 8640) then
  begin
    if Fix_error_now=false then
    begin
      Unit1.Form1.max_fon.Caption:=   IntToStr(address Div 86)+'%';
    end else
    begin
      if(max_fon_massive_ready[address]=false) then Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)-1);
    end;

    max_fon_massive[address]:=massive_element;
    max_fon_massive_ready[address]:=true;

    if(fBuf[0] = $81) then begin
      max_fon_massive[address]:=  fBuf[6];
      max_fon_massive[address+1]:=fBuf[5];
      max_fon_massive[address+2]:=fBuf[4];
      max_fon_massive[address+3]:=fBuf[3];
      max_fon_massive_ready[address]:=true;
      max_fon_massive_ready[address+1]:=true;
      max_fon_massive_ready[address+2]:=true;
      max_fon_massive_ready[address+3]:=true;
    end;


    SetLength(vAns, 1);
    vAns[0]:=$31;
    maxfon_loading_flag:=true;
  end
  else
  begin
    SetLength(vAns, 1);
    vAns[0]:=$32;
    maxfon_loading_flag:=false;
    doze_loading_flag:=true;
  end;

end;
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
if ((fBuf[0] = $f3) or (fBuf[0] = $83)) then begin // �������� �������� ������� ����

  address:=         fBuf[1] shl 8;
  address:=address+ fBuf[2];

  massive_element:=                 fBuf[3] shl 24;
  massive_element:=massive_element+(fBuf[4] shl 16);
  massive_element:=massive_element+(fBuf[5] shl 8);
  massive_element:=massive_element+ fBuf[6];


  if (address < 8640) then
  begin
    if Fix_error_now=false then
    begin
      Unit1.Form1.impulses.Caption:=   IntToStr(address Div 86)+'%';
    end else
    begin
      if(doze_massive_ready[address]=false) then Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)-1);
    end;
    doze_massive[address]:=massive_element;
    doze_massive_ready[address]:=true;

    if(fBuf[0] = $83) then begin
      doze_massive[address]:=  fBuf[6];
      doze_massive[address+1]:=fBuf[5];
      doze_massive[address+2]:=fBuf[4];
      doze_massive[address+3]:=fBuf[3];
      doze_massive_ready[address]:=true;
      doze_massive_ready[address+1]:=true;
      doze_massive_ready[address+2]:=true;
      doze_massive_ready[address+3]:=true;
    end;


    SetLength(vAns, 1);
    vAns[0]:=$32;
    doze_loading_flag:=true;
  end
  else
  begin
    SetLength(vAns, 1);
    vAns[0]:=$39;
    StopRS232:=TRUE;

    Unit1.Form1.errors.Caption:='0';
    for iy := 0 to 8640-1 do begin
      if(max_fon_massive_ready[iy]=false) then Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)+1);
      if(doze_massive_ready[iy]=false)    then Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)+1);
    end;

    if(StrToInt(Unit1.Form1.errors.Caption)=0) then
    begin
      USB_massive_loading:=false;

      Unit1.Form1.Loading.Caption:=loading_lang;
      Unit1.Form1.Refresh;

/////////////////////////////////////////////////////////////////////////////////////
  // �������� ������ �� ������
    begin
      reg := TRegistry.Create;                              // ��������� ������
      reg.RootKey := HKEY_CURRENT_USER;
      reg.OpenKey('Software\USB_Geiger\USB_Geiger', false);
      key := reg.ReadString('Reg_key');
      reg.CloseKey;                                          // ��������� ������
      if key <> '' then
      begin
        data := TIdMultiPartFormDataStream.Create;
        AIdHTTP := TIdHTTP.Create(nil);
        AIdHTTP.HandleRedirects := true;
        try
          // ��������� ������ ���������
          for ix := 0 to 8640 do begin
            if doze_massive[ix]>0 then
              data.AddFormField(IntToStr(ix), IntToStr(((doze_massive[ix] * geiger_seconds_count) Div 600)));
          end;
          IdHTTP1.Post(Concat('http://upload.xn--h1aeegel.net/upload.php?id=',key), data);
          used_len:=(Length(aData)-1); // ������������� ��������� ����
        except
          begin
          end;
        end;
        AIdHTTP.Disconnect;
        AIdHTTP.Free;
        data.Free;
      end;
    end;
/////////////////////////////////////////////////////////////////////////////////////

      Unit1.Form1.Loading.Caption:='';
      Unit1.Form1.Refresh;

      Draw_massive();
      Unit1.Form1.Close;


      maxfon_loading_flag:=false;
      doze_loading_flag:=false;
      Fix_error_now:=false;
    end
    else
    begin
      sleep(200);
      Fix_error_now:=true;
      SetLength(vAns, 1);
      vAns[0]:=$31;
    end;
  end;

end;
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
if (fBuf[0] = $f5) then begin // �������� ��������

  geiger_seconds_count:=                      fBuf[1] shl 8;
  geiger_seconds_count:=geiger_seconds_count+ fBuf[2];
end;
//-----------------------------------------------------------------------------------

end;

end;

RS232.Send(vAns);
if(StopRS232 = TRUE) then
begin
  RS232.StopListner;
  RS232.Close;
end;

if(USB_massive_loading = false) then
begin
  RS232.StopListner;
  RS232.Close;
  if((Voltage_level Div 10) Mod 100)>9 then
  begin
   Voltage.Caption:=voltage_lang+IntToStr(Voltage_level Div 1000)+'.'+IntToStr((Voltage_level Div 10) Mod 100)+' V';
  end
  else
  begin
   Voltage.Caption:=voltage_lang+IntToStr(Voltage_level Div 1000)+'.0'+IntToStr((Voltage_level Div 10) Mod 100)+' V';
  end;
end;
end;
//================================================================================================================

procedure TmainFrm.DoOnSendedEvent(Sender: TObject; const aData: TiaBuf;
  aCount: Cardinal);
Var
  F: INteger;
  ss: String;
begin
  ss := '';
  For F := 0 To Length(aData) - 1 do
    ss := ss + IntToHex(aData[F],2) + ' ';

end;


end.
