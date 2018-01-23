#ifndef SRC_FRC5572Controller_H_
#define SRC_FRC5572Controller_H_

#include <utility>
#include <XboxController.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define LEFT_z 2
#define LEFT_x 0
#define LEFT_y 1

#define RIGHT_z 3
#define RIGHT_x 4
#define RIGHT_y 5

#define LEFT_BUTTON 5
#define RIGHT_BUTTON 6

#define X_BUTTON 3
#define Y_BUTTON 4
#define A_BUTTON 1
#define B_BUTTON 2

#define START_BUTTON 8
#define BACK_BUTTON 7

#define LEFT_STICK_BUTTON 9
#define RIGHT_STICK_BUTTON 10

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/*! \brief Logitech Game Controller
 */
class FRC5572Controller {
public:
  /*! \brief Constructor
   * Sets up game controller and communication with the Driverstation
   * \param x The value associated with the controller. To determine this, open the drivestation and go to the controllers tab. Press any button on the controller. Whichever controller on the list highlights green is the controller, and the number next to it is the one you should insert here.
   */
  FRC5572Controller(int x);
  /*! \brief Default destructor
   */
  ~FRC5572Controller();
  /*! \brief Returns the value of the left trigger
   * The value returned will be between 0 and 1, with 0 being fully depressed and 1 being fully pressed
   */
  double LT();
  /*! \brief Returns the value of the left bumper
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool LB();
  /*! \brief Returns the value of the right trigger
   * The value returned will be between 0 and 1, with 0 being fully depressed and 1 being fully pressed
   */
  double RT();
  /*! \brief Returns the value of the right bumper
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool RB();
  /*! \brief Returns the value of the blue X button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool X();
  /*! \brief Returns the value of the yellow Y button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool Y();
  /*! \brief Returns the value of the green A button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool A();
  /*! \brief Returns the value of the red B button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool B();
  /*! \brief Returns the values from the left joystick
   * The value returned is a pair, with the first value being the x-coordinate of the joystick and the second value being the y-coordinate. The coordinates can be any value from -1 to 1, with 1 being fully up/right, -1 being fully down/left, and 0 being untouched.
   */
  std::pair<double, double> L();
  /*! \brief Returns the values from the right joystick
   * The value returned is a pair, with the first value being the x-coordinate of the joystick and the second value being the y-coordinate. The coordinates can be any value from -1 to 1, with 1 being fully up/right, -1 being fully down/left, and 0 being untouched.
   */
  std::pair<double, double> R();
  /*! \brief Returns the values from the D Pad.
   * The value returned is an integer value which describes the location being pressed on the D Pad, with 0 being the upwards direction, and each other value may be taken as the degrees (from 0 to 360). If none of the buttons are being pressed, -1 is returned instead. 
   */
  int POV();
  /*! \brief Returns the value of the start button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool start();
  /*! \brief Returns the value of the back button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool back();
  /*! \brief Returns the value of the left button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool Lbutton();
  /*! \brief Returns the value of the right button
   * The value returned will be true if the button is pressed, and false otherwise
   */
  bool Rbutton();
  /*! \brief Non-functional member function, which doesn't do anything.
   * It may do something in the future, with a different controller possibly.
   */
  void rumble(double, double);
private:
  frc::XboxController *pad;
};

#endif
