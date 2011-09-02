#ifndef DYNAMIC_GRAPH_ROS_IMPORT_HH
# define DYNAMIC_GRAPH_ROS_IMPORT_HH
# include <iostream>
# include <map>

# include <boost/shared_ptr.hpp>

# include <dynamic-graph/entity.h>
# include <dynamic-graph/signal-time-dependent.h>
# include <dynamic-graph/command.h>

# include <ros/ros.h>

# include "converter.hh"
# include "sot_to_ros.hh"

namespace dynamicgraph
{
  class RosImport;

  namespace command
  {
    namespace rosImport
    {
      using ::dynamicgraph::command::Command;
      using ::dynamicgraph::command::Value;

# define ROS_IMPORT_MAKE_COMMAND(CMD)			\
      class CMD : public Command			\
      {							\
      public:						\
	CMD (RosImport& entity,				\
	     const std::string& docstring);		\
	virtual Value doExecute ();			\
      }

      ROS_IMPORT_MAKE_COMMAND(Add);
      ROS_IMPORT_MAKE_COMMAND(Clear);
      ROS_IMPORT_MAKE_COMMAND(List);
      ROS_IMPORT_MAKE_COMMAND(Rm);

#undef ROS_IMPORT_MAKE_COMMAND

    } // end of namespace errorEstimator.
  } // end of namespace command.


  /// \brief Publish dynamic-graph information into ROS.
  class RosImport : public dynamicgraph::Entity
  {
    DYNAMIC_GRAPH_ENTITY_DECL();
  public:
    typedef std::pair<boost::shared_ptr<dynamicgraph::SignalBase<int> >,
		      boost::shared_ptr<ros::Publisher> >
      bindedSignal_t;

    RosImport (const std::string& n);
    virtual ~RosImport ();

    void display (std::ostream& os) const;

    void add (const std::string& signal, const std::string& topic);
    void rm (const std::string& signal);
    void list ();
    void clear ();

    template <typename T>
    T& sendData (boost::shared_ptr<ros::Publisher> publisher,
		 T& data, int time);

    template <typename T>
    void add (const std::string& signal, const std::string& topic);

  private:
    ros::NodeHandle nh_;
    std::map<std::string, bindedSignal_t> bindedSignal_;
  };
} // end of namespace dynamicgraph.

# include "ros_import.hxx"
#endif //! DYNAMIC_GRAPH_ROS_IMPORT_HH