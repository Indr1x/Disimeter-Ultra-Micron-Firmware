unit About_f;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, pngimage, ExtCtrls, Registry, iaRS232;

type
  TAbout = class(TForm)
    Label1: TLabel;
    Image1: TImage;
    Button1: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit1: TEdit;
    Label6: TLabel;
    Edit2: TEdit;
    Label7: TLabel;
    Timer1: TTimer;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Label8: TLabel;
    Memo1: TMemo;
    Button2: TButton;
    Timer2: TTimer;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  About: TAbout;

implementation

{$R *.dfm}
uses main;

procedure TAbout.Button1Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
begin
About_f.About.Timer2.Enabled := false;
try
   if Edit3.Text <> '' then
   if Edit4.Text <> '' then
   if Edit5.Text <> '' then
   if Edit6.Text <> '' then
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin
         //DevPresent:=true;
         SetLength(vAns, 5);

         vAns[0]:=$e3;

         tmp:=        StrToInt('$'+Copy(Edit3.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit3.Text, 3, 2));
         vAns[1]:=tmp-StrToInt('$'+Copy(Edit3.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit4.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit4.Text, 3, 2));
         vAns[2]:=tmp-StrToInt('$'+Copy(Edit4.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit5.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit5.Text, 3, 2));
         vAns[3]:=tmp-StrToInt('$'+Copy(Edit5.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit6.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit6.Text, 3, 2));
         vAns[4]:=tmp-StrToInt('$'+Copy(Edit6.Text, 1, 2));

         mainFrm.RS232.Send(vAns);
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

  reg := TRegistry.Create;                               // ��������� ������
  reg.RootKey := HKEY_CURRENT_USER;                      // ��� �������� ������������
  reg.OpenKey('Software\Micron\Ultra-Micron', true); // ��������� ������
  reg.WriteString('Reg_key', Edit1.Text);
  reg.CloseKey;                                          // ��������� ������
  reg.Free;
  About.Close;
end;


procedure TAbout.Button2Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
  ix: uint32;
begin
About_f.About.Timer2.Enabled := true;

 for ix := 0 to 18 do begin
  calibration_data[ix]:='';
 end;


try
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin
         //DevPresent:=true;
         SetLength(vAns, 1);

         vAns[0]:=$35;
         mainFrm.RS232.Send(vAns);
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

end;

procedure TAbout.FormCreate(Sender: TObject);
var
  reg: TRegistry;
begin

  reg := TRegistry.Create;                              // ��������� ������
  reg.RootKey := HKEY_CURRENT_USER;
  reg.OpenKey('Software\Micron\Ultra-Micron', true); // ��������� ������
  Edit1.Text := reg.ReadString('Reg_key');
  reg.CloseKey;                                          // ��������� ������
end;

procedure TAbout.Timer1Timer(Sender: TObject);
begin
 About_f.About.Edit2.Text := IntToHex(device_serial_0,8)+ ' ' +IntToHex(device_serial_1,8)+ ' ' +IntToHex(device_serial_2,8);
end;

procedure TAbout.Timer2Timer(Sender: TObject);
var
 ix: uint32;
begin

 About_f.About.Memo1.Lines.Clear;
 About_f.About.Memo1.Lines.Add('����� � ���������� '+Main.geiger_seconds_count.ToString()+', ������ ������:');
 for ix := 0 to 18 do begin
  if (calibration_data[ix] <> '') then
  begin
   About_f.About.Memo1.Lines.Add(calibration_data[ix]);
  end
   else
   begin
     About_f.About.Memo1.Lines.Add('***');
   end;
 end;

  if (calibration_data[18] <> '') then
  begin
   About_f.About.Timer2.Enabled := false;
   ShowMessage('������ ���������� ��������.');
  end;

  end;

end.
