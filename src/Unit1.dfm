object Form1: TForm1
  Left = 201
  Top = 207
  Width = 1049
  Height = 717
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1033
    Height = 678
    ActivePage = PageResults
    Align = alClient
    TabIndex = 2
    TabOrder = 0
    object PagePorts: TTabSheet
      Caption = 'LPT and COM'
      object GroupBox1: TGroupBox
        Left = 8
        Top = 0
        Width = 289
        Height = 89
        Caption = 'LPT port & commutator'
        TabOrder = 0
        object btCloseLPT: TButton
          Left = 94
          Top = 16
          Width = 75
          Height = 25
          Caption = 'close LPT'
          TabOrder = 0
          OnClick = btCloseLPTClick
        end
        object btNextPort: TButton
          Left = 176
          Top = 48
          Width = 89
          Height = 25
          Caption = '+'
          TabOrder = 1
          OnClick = btNextPortClick
        end
        object btLEDtest: TButton
          Left = 176
          Top = 16
          Width = 89
          Height = 25
          Caption = 'LED test'
          TabOrder = 2
          OnClick = btLEDtestClick
        end
        object btOpenLPT: TButton
          Left = 14
          Top = 16
          Width = 75
          Height = 25
          Caption = 'open LPT'
          TabOrder = 3
          OnClick = btOpenLPTClick
        end
        object btWriteLPT: TButton
          Left = 94
          Top = 48
          Width = 75
          Height = 25
          Caption = 'write'
          TabOrder = 4
          OnClick = btWriteLPTClick
        end
        object Edit1: TEdit
          Left = 16
          Top = 52
          Width = 73
          Height = 21
          TabOrder = 5
          Text = '0'
        end
      end
      object GroupBox2: TGroupBox
        Left = 312
        Top = 0
        Width = 201
        Height = 89
        Caption = 'Com port'
        TabOrder = 1
        object btOpenCOM: TButton
          Left = 14
          Top = 16
          Width = 75
          Height = 25
          Caption = 'open COM'
          TabOrder = 0
          OnClick = btOpenCOMClick
        end
        object btCloseCOM: TButton
          Left = 14
          Top = 40
          Width = 75
          Height = 25
          Caption = 'close COM'
          TabOrder = 1
          OnClick = btCloseCOMClick
        end
      end
    end
    object PageTasks: TTabSheet
      Caption = 'Tasks'
      ImageIndex = 1
      DesignSize = (
        1025
        650)
      object Label2: TLabel
        Left = 14
        Top = 36
        Width = 75
        Height = 13
        Caption = #1082#1086#1085#1077#1095#1085#1099#1081' '#1087#1086#1088#1090
      end
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 81
        Height = 13
        Caption = #1085#1072#1095#1072#1083#1100#1085#1099#1081' '#1087#1086#1088#1090
      end
      object Label3: TLabel
        Left = 18
        Top = 94
        Width = 95
        Height = 13
        Caption = #1079#1072#1076#1072#1085#1080#1081' '#1074' '#1086#1095#1077#1088#1077#1076#1080
      end
      object LTaskCount: TLabel
        Left = 128
        Top = 89
        Width = 9
        Height = 20
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object btGenerateTasks: TButton
        Left = 352
        Top = 36
        Width = 137
        Height = 25
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1047#1072#1076#1072#1085#1080#1103
        TabOrder = 0
        OnClick = btGenerateTasksClick
      end
      object bt_Profile8: TButton
        Left = 352
        Top = 8
        Width = 137
        Height = 25
        Caption = #1087#1088#1086#1092#1080#1083#1103' '#1074#1089#1077' 8'
        TabOrder = 1
        OnClick = bt_Profile8Click
      end
      object bt_SendCommand: TButton
        Left = 376
        Top = 64
        Width = 113
        Height = 25
        Caption = #1055#1086#1089#1083#1072#1090#1100' '#1082#1086#1084#1072#1085#1076#1091
        TabOrder = 2
        OnClick = bt_SendCommandClick
      end
      object ComboBox1: TComboBox
        Left = 8
        Top = 64
        Width = 361
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Items.Strings = (
          ''
          'admin'
          'system set cli timeout no'
          'adsl show port admin status'
          'adsl show port oper status'
          'adsl show current port profiles'
          'system set trap adsl ena')
      end
      object Estart: TEdit
        Left = 96
        Top = 8
        Width = 65
        Height = 21
        TabOrder = 4
        Text = '1'
      end
      object Eend: TEdit
        Left = 96
        Top = 36
        Width = 65
        Height = 21
        TabOrder = 5
        Text = '16'
      end
      object Memo2: TMemo
        Left = 8
        Top = 128
        Width = 1001
        Height = 505
        Anchors = [akLeft, akTop, akRight, akBottom]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Pitch = fpFixed
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 6
      end
      object Button1_64: TButton
        Left = 176
        Top = 8
        Width = 33
        Height = 25
        Caption = '1-64'
        TabOrder = 7
        OnClick = Button1_64Click
      end
      object Button1_16: TButton
        Left = 176
        Top = 36
        Width = 35
        Height = 25
        Caption = '1-16'
        TabOrder = 8
        OnClick = Button1_16Click
      end
      object Button33_48: TButton
        Left = 256
        Top = 36
        Width = 35
        Height = 25
        Caption = '33-48'
        TabOrder = 9
        OnClick = Button33_48Click
      end
      object Button49_64: TButton
        Left = 296
        Top = 36
        Width = 35
        Height = 25
        Caption = '49-64'
        TabOrder = 10
        OnClick = Button49_64Click
      end
      object Button17_32: TButton
        Left = 216
        Top = 36
        Width = 35
        Height = 25
        Caption = '17-32'
        TabOrder = 11
        OnClick = Button17_32Click
      end
      object bt_SendCommands: TButton
        Left = 912
        Top = 80
        Width = 113
        Height = 41
        Caption = #1087#1086#1089#1083#1072#1090#1100' '#1082#1086#1084#1072#1085#1076#1099
        TabOrder = 12
        OnClick = bt_SendCommandsClick
      end
      object Memo_Commands: TMemo
        Left = 496
        Top = 8
        Width = 409
        Height = 113
        Lines.Strings = (
          'adsl set port profile 8 -maxrateds 16000'#9
          'adsl set port profile 8 -minrateds 32'#9
          'adsl set port profile 8 -maxrateus 1600'#9
          'adsl set port profile 8 -minrateus 32'#9
          'adsl set port profile 8 -marginds 6'#9
          'adsl set port profile 8 -marginus 6'#9
          'adsl set port profile 8 -maxdelayds 16'#9
          'adsl set port profile 8 -maxdelayus 8'#9
          'adsl set port profile 8 -mininpds 1s'#9
          'adsl set port profile 8 -mininpus 1s'#9
          'adsl set port profile 8 -bitswapds ena'#9
          'adsl set port profile 8 -bitswapus ena'#9
          'adsl set port profile 8 -ramodeds dynamicra'#9
          'adsl set port profile 8 -ramodeus dynamicra'#9
          'adsl set port profile 8 -annex 992.5'#9)
        TabOrder = 13
      end
      object btClearQueue: TButton
        Left = 152
        Top = 88
        Width = 89
        Height = 25
        Caption = 'Clear queue'
        TabOrder = 14
        OnClick = btClearQueueClick
      end
    end
    object PageResults: TTabSheet
      Caption = 'Results'
      ImageIndex = 2
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 1025
        Height = 650
        VertScrollBar.Tracking = True
        Align = alClient
        TabOrder = 0
        OnMouseWheelDown = ScrollBox1MouseWheelDown
        OnMouseWheelUp = ScrollBox1MouseWheelUp
        object btExport: TButton
          Left = 928
          Top = 8
          Width = 89
          Height = 25
          Caption = 'Export'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = btExportClick
        end
        object btImport: TButton
          Left = 928
          Top = 36
          Width = 89
          Height = 25
          Caption = 'Import'
          TabOrder = 1
          OnClick = btImportClick
        end
        object LabeledEdit1: TLabeledEdit
          Left = 924
          Top = 104
          Width = 97
          Height = 21
          EditLabel.Width = 89
          EditLabel.Height = 13
          EditLabel.Caption = 'Attainable Rate Ds'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
          Text = '24000'
          OnChange = LabeledEditParamChange
        end
        object LabeledEdit2: TLabeledEdit
          Tag = 1
          Left = 924
          Top = 152
          Width = 97
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'Ds Line Rate'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
          Text = '15000'
          OnChange = LabeledEditParamChange
        end
        object LabeledEdit3: TLabeledEdit
          Tag = 2
          Left = 924
          Top = 200
          Width = 97
          Height = 21
          EditLabel.Width = 89
          EditLabel.Height = 13
          EditLabel.Caption = 'Attainable Rate Us'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
          Text = '1100'
          OnChange = LabeledEditParamChange
        end
        object LabeledEdit4: TLabeledEdit
          Tag = 3
          Left = 924
          Top = 248
          Width = 97
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'Us Line Rate'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 5
          Text = '1000'
          OnChange = LabeledEditParamChange
        end
        object LabeledEdit5: TLabeledEdit
          Tag = 4
          Left = 924
          Top = 304
          Width = 97
          Height = 21
          EditLabel.Width = 95
          EditLabel.Height = 13
          EditLabel.Caption = 'DS Line Attenuation'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
          Text = '6'
          OnChange = LabeledEditParamChange
        end
        object LabeledEdit6: TLabeledEdit
          Tag = 5
          Left = 924
          Top = 360
          Width = 97
          Height = 21
          EditLabel.Width = 95
          EditLabel.Height = 13
          EditLabel.Caption = 'US Line Attenuation'
          EditLabel.WordWrap = True
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 7
          Text = '10'
          OnChange = LabeledEditParamChange
        end
        object btApplyLimits: TButton
          Left = 920
          Top = 392
          Width = 105
          Height = 33
          Caption = 'Apply limits'
          TabOrder = 8
          OnClick = btApplyLimitsClick
        end
      end
    end
    object PageLog: TTabSheet
      Caption = 'log'
      ImageIndex = 3
      DesignSize = (
        1025
        650)
      object Memo1: TMemo
        Left = 8
        Top = 4
        Width = 1001
        Height = 629
        Anchors = [akLeft, akTop, akRight, akBottom]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Pitch = fpFixed
        Font.Style = []
        Lines.Strings = (
          'Memo1')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 960
    Top = 488
  end
  object Timer_heartbeat: TTimer
    OnTimer = Timer_heartbeatTimer
    Left = 928
    Top = 488
  end
  object OpenDialog1: TOpenDialog
    Left = 992
    Top = 488
  end
  object SaveDialog1: TSaveDialog
    Left = 992
    Top = 520
  end
end
