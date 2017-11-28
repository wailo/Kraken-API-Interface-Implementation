#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

class view_controller
{
 public:
  //! Default constructor
  view_controller();

  //! Copy constructor
  view_controller(const view_controller &other);

  //! Move constructor
  view_controller(view_controller &&other) noexcept;

  //! Destructor
  virtual ~view_controller() noexcept;

  //! Copy assignment operator
  view_controller& operator=(const view_controller &other);

  //! Move assignment operator
  view_controller& operator=(view_controller &&other) noexcept;

  // Display all open orders.
  // Send an order.
  // Cancel all orders.
  

 protected:
 private:
};


#endif /* VIEW_CONTROLLER_H */
