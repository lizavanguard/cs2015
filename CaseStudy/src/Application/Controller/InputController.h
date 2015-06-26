//******************************************************************************
//
// ���͐��䏈��  [InputController.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/19
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************


//******************************************************************************
// ���C�u�����̃����N
//******************************************************************************


//******************************************************************************
// �}�N����`
//******************************************************************************


//******************************************************************************
// �\���̒�`
//******************************************************************************


//******************************************************************************
// �N���X��`
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
// �v���g�^�C�v�錾
//******************************************************************************



#endif
// EOF