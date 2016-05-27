#include <comnet.h>
#include <xbee.h>

void* on_pong(int8_t link_id, com_header_t header, pong_t pong, comnet::node* node);
void* on_vehicle_authorization_request(int8_t link_id, com_header_t header, vehicle_authorization_request_t vehicle_authorization_request, comnet::node* node);
void* on_vehicle_telemetry_command(int8_t link_id, com_header_t header, vehicle_telemetry_command_t vehicle_telemetry_command, comnet::node* node);
void* on_vehicle_waypoint_command(int8_t link_id, com_header_t header, vehicle_waypoint_command_t vehicle_waypoint_command, comnet::node* node);
void* on_target_designation_command(int8_t link_id, com_header_t header, target_designation_command_t target_designation_command, comnet::node* node);
void* on_payload_bay_command(int8_t link_id, com_header_t header, payload_bay_command_t payload_bay_command, comnet::node* node);
void* on_vehicle_mode_command(int8_t link_id, com_header_t header, vehicle_mode_command_t vehicle_mode_command, comnet::node* node);