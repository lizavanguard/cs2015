//******************************************************************************
//
// 入力制御処理  [InputController.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/19
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************


//******************************************************************************
// ライブラリのリンク
//******************************************************************************


//******************************************************************************
// マクロ定義
//******************************************************************************


//******************************************************************************
// 構造体定義
//******************************************************************************


//******************************************************************************
// クラス定義
//******************************************************************************
class InputKeyboard;
class InputDevice;
class InputController{
  public:
  typedef struct{
//      InputKeyboard* p_inputKeyboard;
//      InputDevice* p_inputDevice;
//      InputDevice* p_inputDevice;
      bool inputKeyboard;
      bool inputDevice;
  }InputControl;

  // modemanaged
  enum ControlState{
      UP = 0,
      DOWN,
      LEFT,
      RIGHT,
      BOTTON_1,
      BOTTON_2,
      BOTTON_3,
      BOTTON_4,
      BOTTON_R1,
      BOTTON_R2,
      BOTTON_L1,
      BOTTON_L2,
      BOTTON_START,
      BOTTON_SELECT,
      kControllerMax,
  };

  // funciton ==================================
public:
  // ctor
    InputController();
  // dtor
    virtual ~InputController();
  // update
  void Update();

  // get
  //bool IsPress(int key) const { return is_Press_ControlKey_[controlKey_[key]]; }
  //bool IsRelease(int key) const { return is_Release_ControlKey_[controlKey_[key]]; }
  //bool IsRepeat(int key) const { return is_Repeat_ControlKey_[controlKey_[key]]; }
  //bool IsTrigger(int key) const { return is_Trigger_ControlKey_[controlKey_[key]]; }
  void IsPress(int key);

  // set
  void SetControlKey(int currentKey, int destKey){ controlKey_[currentKey] = defaultKey_[destKey]; }

protected:

private:


  // parameter =================================
public:

protected:

private:
    bool is_Press_ControlKey_[kControllerMax];
    bool is_Trigger_ControlKey_[kControllerMax];
    bool is_Release_ControlKey_[kControllerMax];
    bool is_Repeat_ControlKey_[kControllerMax];

    int controlKey_[kControllerMax];
//    int controlPad_[kControllerMax];
    int defaultKey_[kControllerMax];

    InputControl p_controller_[kControllerMax];
};

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************



#endif
// EOF