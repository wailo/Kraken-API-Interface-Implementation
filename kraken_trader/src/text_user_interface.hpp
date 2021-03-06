#ifndef TEXT_USER_INTERFACE_H
#define TEXT_USER_INTERFACE_H

#include <string>
#include <vector>

class text_user_interface {
public:
  //! Default constructor
  text_user_interface();

  // //! Copy constructor
  // text_user_interface(const text_user_interface &other);

  // //! Move constructor
  // text_user_interface(text_user_interface &&other) noexcept;

  //! Destructor
  ~text_user_interface() noexcept;

  // //! Copy assignment operator
  // text_user_interface& operator=(const text_user_interface &other);

  // //! Move assignment operator
  // text_user_interface& operator=(text_user_interface &&other) noexcept;

  bool set_orders(const std::vector<std::string> &&orders);

private:
  std::vector<std::string> m_orders;
};

#endif /* TEXT_USER_INTERFACE_H */
