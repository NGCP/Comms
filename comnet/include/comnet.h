/**@file This file was autogenerated. All changes will be undone. */

#ifndef _COMNET_H_
#define _COMNET_H_

/*Include files*/ 
#include <datalink.h>
#include <comnet_protocol.h>
#include <pqueue.h>
#include <threadCom.h>
#include <string>
#include <error_handle.h>
namespace comnet
{
   /*Let compiler know class node exists some where else */ 
   class node;

   /**Global function call back used for message Enter must be implemented on platform for use*/ 
   typedef void* (*enter_callback)(int8_t, com_header_t, enter_t, comnet::node* node_ptr);
   /**Global function call back used for message Exit must be implemented on platform for use*/ 
   typedef void* (*exit_callback)(int8_t, com_header_t, exit_t, comnet::node* node_ptr);
   /**Global function call back used for message Ping must be implemented on platform for use*/ 
   typedef void* (*ping_callback)(int8_t, com_header_t, ping_t, comnet::node* node_ptr);
   /**Global function call back used for message Pong must be implemented on platform for use*/ 
   typedef void* (*pong_callback)(int8_t, com_header_t, pong_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Identification must be implemented on platform for use*/ 
   typedef void* (*vehicle_identification_callback)(int8_t, com_header_t, vehicle_identification_t, comnet::node* node_ptr);
   /**Global function call back used for message Amy_Stuff must be implemented on platform for use*/ 
   typedef void* (*amy_stuff_callback)(int8_t, com_header_t, amy_stuff_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Authorization_Request must be implemented on platform for use*/ 
   typedef void* (*vehicle_authorization_request_callback)(int8_t, com_header_t, vehicle_authorization_request_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Authorization_Reply must be implemented on platform for use*/ 
   typedef void* (*vehicle_authorization_reply_callback)(int8_t, com_header_t, vehicle_authorization_reply_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Mode_Command must be implemented on platform for use*/ 
   typedef void* (*vehicle_mode_command_callback)(int8_t, com_header_t, vehicle_mode_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Termination_Command must be implemented on platform for use*/ 
   typedef void* (*vehicle_termination_command_callback)(int8_t, com_header_t, vehicle_termination_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Telemetry_Command must be implemented on platform for use*/ 
   typedef void* (*vehicle_telemetry_command_callback)(int8_t, com_header_t, vehicle_telemetry_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Waypoint_Command must be implemented on platform for use*/ 
   typedef void* (*vehicle_waypoint_command_callback)(int8_t, com_header_t, vehicle_waypoint_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_System_Status must be implemented on platform for use*/ 
   typedef void* (*vehicle_system_status_callback)(int8_t, com_header_t, vehicle_system_status_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Inertial_State must be implemented on platform for use*/ 
   typedef void* (*vehicle_inertial_state_callback)(int8_t, com_header_t, vehicle_inertial_state_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Global_Position must be implemented on platform for use*/ 
   typedef void* (*vehicle_global_position_callback)(int8_t, com_header_t, vehicle_global_position_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Body_Sensed_State must be implemented on platform for use*/ 
   typedef void* (*vehicle_body_sensed_state_callback)(int8_t, com_header_t, vehicle_body_sensed_state_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Attitude must be implemented on platform for use*/ 
   typedef void* (*vehicle_attitude_callback)(int8_t, com_header_t, vehicle_attitude_t, comnet::node* node_ptr);
   /**Global function call back used for message Vehicle_Ground_Relative_State must be implemented on platform for use*/ 
   typedef void* (*vehicle_ground_relative_state_callback)(int8_t, com_header_t, vehicle_ground_relative_state_t, comnet::node* node_ptr);
   /**Global function call back used for message Payload_Bay_Command must be implemented on platform for use*/ 
   typedef void* (*payload_bay_command_callback)(int8_t, com_header_t, payload_bay_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Payload_Bay_Mode_Command must be implemented on platform for use*/ 
   typedef void* (*payload_bay_mode_command_callback)(int8_t, com_header_t, payload_bay_mode_command_t, comnet::node* node_ptr);
   /**Global function call back used for message Target_Designation_Command must be implemented on platform for use*/ 
   typedef void* (*target_designation_command_callback)(int8_t, com_header_t, target_designation_command_t, comnet::node* node_ptr);
   /**Global function call back used for message UGV_Joystick must be implemented on platform for use*/ 
   typedef void* (*UGV_joystick_callback)(int8_t, com_header_t, UGV_joystick_t, comnet::node* node_ptr);
   /**Global function call back used for message UGV_Battery_Status must be implemented on platform for use*/ 
   typedef void* (*UGV_battery_status_callback)(int8_t, com_header_t, UGV_battery_status_t, comnet::node* node_ptr);
   
	/** Class node represents each point of communication. The Node will be able to establish type of communication and send and receive messages. The callbacks must be implemented on the platform*/
   class node
   {
   public:
      node(uint8_t node_id);
      node(uint8_t node_id, int32_t mode);
      ~node();
      /**Public method used to start node connection and messages*/ 
      void start();

      /** Public method used to add serial communication*/ 
      void add_serial(int8_t* link_id, uint32_t baud_rate, char device_path[50]);
      /** Public method used to add UDP communication*/ 
      void add_udp(int8_t* link_id, uint16_t port);
      /** Public method used to add UDP communication*/ 
      void add_udp(int8_t* link_id, uint16_t port, char addr[16]);

      /** Public method used to add Zigbee communication*/
      void add_zigBee(int8_t* link_id, uint32_t baudRate, char device_path[50]);
      /** Public method used to establixh Zigbee connection*/
      void establish_zigBee(int8_t link_id, uint8_t node_id, std::string address64Hex); 
      /** Public method used to establish serial communication*/ 
      void establish_serial(int8_t link_id, uint8_t node_id);
      /** Public method used to establish UDP communication*/ 
      void establish_udp(int8_t link_id, uint8_t node_id, uint16_t port, char addr[16]);

      /** method returns the number of datalink for this node*/ 
      uint8_t get_num_datalinks();
      /**Public method used to find if datalink is connected*/ 
      int32_t query_datalink_connected(int8_t link_id);
      /**Public method used to find what type of communication the datalink is*/ 
      datalink_type_t query_datalink_type(int8_t link_id);

      /**Public definition of the send Enter message which will be put into the message queue.*/ 
      void send_enter(
         uint8_t dest_id,
         float64_t timestamp,
         bool is_emergency = false);

      /**Public definition of the send Exit message which will be put into the message queue.*/ 
      void send_exit(
         uint8_t dest_id,
         float64_t timestamp,
         bool is_emergency = false);

      /**Public definition of the send Ping message which will be put into the message queue.*/ 
      void send_ping(
         uint8_t dest_id,
         float64_t timestamp,
         bool is_emergency = false);

      /**Public definition of the send Pong message which will be put into the message queue.*/ 
      void send_pong(
         uint8_t dest_id,
         float64_t timestamp,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Identification message which will be put into the message queue.*/ 
      void send_vehicle_identification(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t vehicle_type,
         uint16_t owner_ID,
         bool is_emergency = false);

      /**Public definition of the send Amy_Stuff message which will be put into the message queue.*/ 
      void send_amy_stuff(
         uint8_t dest_id,
         float64_t hello,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Authorization_Request message which will be put into the message queue.*/ 
      void send_vehicle_authorization_request(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t link_key,
         uint8_t requested_services,
         uint8_t handover_node,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Authorization_Reply message which will be put into the message queue.*/ 
      void send_vehicle_authorization_reply(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t vehicle_type,
         uint8_t authorized_services,
         uint8_t granted_services,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Mode_Command message which will be put into the message queue.*/ 
      void send_vehicle_mode_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t vehicle_mode,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Termination_Command message which will be put into the message queue.*/ 
      void send_vehicle_termination_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t termination_mode,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Telemetry_Command message which will be put into the message queue.*/ 
      void send_vehicle_telemetry_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint8_t telemetry_select,
         uint8_t telemetry_rate,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Waypoint_Command message which will be put into the message queue.*/ 
      void send_vehicle_waypoint_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         int32_t latitude,
         int32_t longitude,
         int32_t altitude,
         int32_t heading,
         uint8_t waypoint_ID,
         uint8_t waypoint_type,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_System_Status message which will be put into the message queue.*/ 
      void send_vehicle_system_status(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t vehicle_mode,
         uint8_t vehicle_state,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Inertial_State message which will be put into the message queue.*/ 
      void send_vehicle_inertial_state(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         float64_t latitude,
         float64_t longitude,
         float32_t altitude,
         float32_t roll,
         float32_t pitch,
         float32_t heading,
         float32_t north_speed,
         float32_t east_speed,
         float32_t vertical_speed,
         float32_t roll_rate,
         float32_t pitch_rate,
         float32_t yaw_rate,
         float32_t north_accel,
         float32_t east_accel,
         float32_t vertical_accel,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Global_Position message which will be put into the message queue.*/ 
      void send_vehicle_global_position(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         int32_t latitude,
         int32_t longitude,
         int32_t altitude,
         int32_t heading,
         int16_t x_speed,
         int16_t y_speed,
         int16_t z_speed,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Body_Sensed_State message which will be put into the message queue.*/ 
      void send_vehicle_body_sensed_state(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         int16_t x_accel,
         int16_t y_accel,
         int16_t z_accel,
         int16_t roll_rate,
         int16_t pitch_rate,
         int16_t yaw_rate,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Attitude message which will be put into the message queue.*/ 
      void send_vehicle_attitude(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         float32_t roll,
         float32_t pitch,
         float32_t yaw,
         bool is_emergency = false);

      /**Public definition of the send Vehicle_Ground_Relative_State message which will be put into the message queue.*/ 
      void send_vehicle_ground_relative_state(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         float32_t angle_of_attack,
         float32_t angle_of_sideslip,
         float32_t true_airspeed,
         float32_t indicated_airspeed,
         float32_t north_wind_speed,
         float32_t east_wind_speed,
         float32_t north_ground_speed,
         float32_t east_ground_speed,
         float32_t barometric_pressure,
         float32_t barometric_altitude,
         bool is_emergency = false);

      /**Public definition of the send Payload_Bay_Command message which will be put into the message queue.*/ 
      void send_payload_bay_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint32_t payload_ID,
         uint8_t payload_command,
         bool is_emergency = false);

      /**Public definition of the send Payload_Bay_Mode_Command message which will be put into the message queue.*/ 
      void send_payload_bay_mode_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint32_t payload_ID,
         uint8_t payload_mode,
         bool is_emergency = false);

      /**Public definition of the send Target_Designation_Command message which will be put into the message queue.*/ 
      void send_target_designation_command(
         uint8_t dest_id,
         float64_t timestamp,
         uint16_t vehicle_ID,
         uint8_t payload_ID,
         uint8_t target_ID,
         uint8_t target_type,
         int32_t latitude,
         int32_t longitude,
         int32_t altitude,
         bool is_emergency = false);

      /**Public definition of the send UGV_Joystick message which will be put into the message queue.*/ 
      void send_UGV_joystick(
         uint8_t dest_id,
         float64_t timestamp,
         uint8_t vehicle_id,
         float32_t steering,
         float32_t throttle,
         bool is_emergency = false);

      /**Public definition of the send UGV_Battery_Status message which will be put into the message queue.*/ 
      void send_UGV_battery_status(
         uint8_t dest_id,
         float64_t timestamp,
         float32_t voltage_3_3V,
         float32_t voltage_5V,
         float32_t voltage_12V,
         float32_t current_3_3V,
         float32_t current_5V,
         float32_t current_12V,
         float32_t current_fore_motor,
         float32_t current_aft_motor,
         bool is_emergency = false);

      /**Public definition of the register on Enter message which will use the message call back.*/ 
      void register_on_enter(enter_callback callback){on_enter = callback;}
      /**Public definition of the register on Exit message which will use the message call back.*/ 
      void register_on_exit(exit_callback callback){on_exit = callback;}
      /**Public definition of the register on Ping message which will use the message call back.*/ 
      void register_on_ping(ping_callback callback){on_ping = callback;}
      /**Public definition of the register on Pong message which will use the message call back.*/ 
      void register_on_pong(pong_callback callback){on_pong = callback;}
      /**Public definition of the register on Vehicle_Identification message which will use the message call back.*/ 
      void register_on_vehicle_identification(vehicle_identification_callback callback){on_vehicle_identification = callback;}
      /**Public definition of the register on Amy_Stuff message which will use the message call back.*/ 
      void register_on_amy_stuff(amy_stuff_callback callback){on_amy_stuff = callback;}
      /**Public definition of the register on Vehicle_Authorization_Request message which will use the message call back.*/ 
      void register_on_vehicle_authorization_request(vehicle_authorization_request_callback callback){on_vehicle_authorization_request = callback;}
      /**Public definition of the register on Vehicle_Authorization_Reply message which will use the message call back.*/ 
      void register_on_vehicle_authorization_reply(vehicle_authorization_reply_callback callback){on_vehicle_authorization_reply = callback;}
      /**Public definition of the register on Vehicle_Mode_Command message which will use the message call back.*/ 
      void register_on_vehicle_mode_command(vehicle_mode_command_callback callback){on_vehicle_mode_command = callback;}
      /**Public definition of the register on Vehicle_Termination_Command message which will use the message call back.*/ 
      void register_on_vehicle_termination_command(vehicle_termination_command_callback callback){on_vehicle_termination_command = callback;}
      /**Public definition of the register on Vehicle_Telemetry_Command message which will use the message call back.*/ 
      void register_on_vehicle_telemetry_command(vehicle_telemetry_command_callback callback){on_vehicle_telemetry_command = callback;}
      /**Public definition of the register on Vehicle_Waypoint_Command message which will use the message call back.*/ 
      void register_on_vehicle_waypoint_command(vehicle_waypoint_command_callback callback){on_vehicle_waypoint_command = callback;}
      /**Public definition of the register on Vehicle_System_Status message which will use the message call back.*/ 
      void register_on_vehicle_system_status(vehicle_system_status_callback callback){on_vehicle_system_status = callback;}
      /**Public definition of the register on Vehicle_Inertial_State message which will use the message call back.*/ 
      void register_on_vehicle_inertial_state(vehicle_inertial_state_callback callback){on_vehicle_inertial_state = callback;}
      /**Public definition of the register on Vehicle_Global_Position message which will use the message call back.*/ 
      void register_on_vehicle_global_position(vehicle_global_position_callback callback){on_vehicle_global_position = callback;}
      /**Public definition of the register on Vehicle_Body_Sensed_State message which will use the message call back.*/ 
      void register_on_vehicle_body_sensed_state(vehicle_body_sensed_state_callback callback){on_vehicle_body_sensed_state = callback;}
      /**Public definition of the register on Vehicle_Attitude message which will use the message call back.*/ 
      void register_on_vehicle_attitude(vehicle_attitude_callback callback){on_vehicle_attitude = callback;}
      /**Public definition of the register on Vehicle_Ground_Relative_State message which will use the message call back.*/ 
      void register_on_vehicle_ground_relative_state(vehicle_ground_relative_state_callback callback){on_vehicle_ground_relative_state = callback;}
      /**Public definition of the register on Payload_Bay_Command message which will use the message call back.*/ 
      void register_on_payload_bay_command(payload_bay_command_callback callback){on_payload_bay_command = callback;}
      /**Public definition of the register on Payload_Bay_Mode_Command message which will use the message call back.*/ 
      void register_on_payload_bay_mode_command(payload_bay_mode_command_callback callback){on_payload_bay_mode_command = callback;}
      /**Public definition of the register on Target_Designation_Command message which will use the message call back.*/ 
      void register_on_target_designation_command(target_designation_command_callback callback){on_target_designation_command = callback;}
      /**Public definition of the register on UGV_Joystick message which will use the message call back.*/ 
      void register_on_UGV_joystick(UGV_joystick_callback callback){on_UGV_joystick = callback;}
      /**Public definition of the register on UGV_Battery_Status message which will use the message call back.*/ 
      void register_on_UGV_battery_status(UGV_battery_status_callback callback){on_UGV_battery_status = callback;}

   private:
      /**Private data member hold the node id.*/ 
      uint8_t node_id;

      /**Private data member used to keep track of the number of data links associated with this node*/ 
      int8_t num_datalinks;
      /**Private array used to store all the datalink in this node*/ 
      datalink* datalinks[255];
      /**Private data member to keep track of the threads associated with this node*/ 
      thread_t datalink_threads[255];

      /**Private pointer to the message queue*/ 
      com_msg_queue queue;
      /**Private method to handle the message to determine the type of message and its following actions  */ 
      void handle_com_msg_t(com_msg_t* rx_msg, com_msg_buf_t* rx_buf);

      /**Private data member to hold thread handler*/ 
      thread_t handler_thread;
      /**Private method which is entry point for the event handler that performs callbacks based on incoming messages  */ 
      void* comnet_handler();
      /**Private method Helper functions from C style from C++ entry point with class member linkage*/ 
      static void* handler_helper(void* context);

      /**Private data member to keep track of upkeep thread data.*/ 
      thread_t upkeep_thread;
      /**Private method for posix and windows compatible sleep method*/ 
      void* upkeep_handler();
      /**Private method returns pointer to upkeep_handler*/ 
      static void* upkeep_helper(void* context);

      /**Private methods sets all call backs to null */ 
      void null_callback_storage();

      /**Private data declares on Enter as call back data type used to hold call back*/ 
      enter_callback on_enter;
      /**Private data declares on Exit as call back data type used to hold call back*/ 
      exit_callback on_exit;
      /**Private data declares on Ping as call back data type used to hold call back*/ 
      ping_callback on_ping;
      /**Private data declares on Pong as call back data type used to hold call back*/ 
      pong_callback on_pong;
      /**Private data declares on Vehicle_Identification as call back data type used to hold call back*/ 
      vehicle_identification_callback on_vehicle_identification;
      /**Private data declares on Amy_Stuff as call back data type used to hold call back*/ 
      amy_stuff_callback on_amy_stuff;
      /**Private data declares on Vehicle_Authorization_Request as call back data type used to hold call back*/ 
      vehicle_authorization_request_callback on_vehicle_authorization_request;
      /**Private data declares on Vehicle_Authorization_Reply as call back data type used to hold call back*/ 
      vehicle_authorization_reply_callback on_vehicle_authorization_reply;
      /**Private data declares on Vehicle_Mode_Command as call back data type used to hold call back*/ 
      vehicle_mode_command_callback on_vehicle_mode_command;
      /**Private data declares on Vehicle_Termination_Command as call back data type used to hold call back*/ 
      vehicle_termination_command_callback on_vehicle_termination_command;
      /**Private data declares on Vehicle_Telemetry_Command as call back data type used to hold call back*/ 
      vehicle_telemetry_command_callback on_vehicle_telemetry_command;
      /**Private data declares on Vehicle_Waypoint_Command as call back data type used to hold call back*/ 
      vehicle_waypoint_command_callback on_vehicle_waypoint_command;
      /**Private data declares on Vehicle_System_Status as call back data type used to hold call back*/ 
      vehicle_system_status_callback on_vehicle_system_status;
      /**Private data declares on Vehicle_Inertial_State as call back data type used to hold call back*/ 
      vehicle_inertial_state_callback on_vehicle_inertial_state;
      /**Private data declares on Vehicle_Global_Position as call back data type used to hold call back*/ 
      vehicle_global_position_callback on_vehicle_global_position;
      /**Private data declares on Vehicle_Body_Sensed_State as call back data type used to hold call back*/ 
      vehicle_body_sensed_state_callback on_vehicle_body_sensed_state;
      /**Private data declares on Vehicle_Attitude as call back data type used to hold call back*/ 
      vehicle_attitude_callback on_vehicle_attitude;
      /**Private data declares on Vehicle_Ground_Relative_State as call back data type used to hold call back*/ 
      vehicle_ground_relative_state_callback on_vehicle_ground_relative_state;
      /**Private data declares on Payload_Bay_Command as call back data type used to hold call back*/ 
      payload_bay_command_callback on_payload_bay_command;
      /**Private data declares on Payload_Bay_Mode_Command as call back data type used to hold call back*/ 
      payload_bay_mode_command_callback on_payload_bay_mode_command;
      /**Private data declares on Target_Designation_Command as call back data type used to hold call back*/ 
      target_designation_command_callback on_target_designation_command;
      /**Private data declares on UGV_Joystick as call back data type used to hold call back*/ 
      UGV_joystick_callback on_UGV_joystick;
      /**Private data declares on UGV_Battery_Status as call back data type used to hold call back*/ 
      UGV_battery_status_callback on_UGV_battery_status;
   };
}
#endif