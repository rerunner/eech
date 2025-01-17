#ifndef CO_UNDERCARRIAGE_H_
#define CO_UNDERCARRIAGE_H_

void initialise_undercarriage_database(void);
void deinitialise_undercarriage_database(void);

void initialise_undercarriage_dynamics(void);
void deinitialise_undercarriage_dynamics(void);

void update_undercarriage_dynamics(void);

void reset_undercarriage_world_position(void);

int helicopter_has_undercarriage_modelling(void);

void repair_wheels(void);

int nose_wheel_locked_down(void);
int left_main_wheel_locked_down(void);
int right_main_wheel_locked_down(void);

int weight_on_wheels(void);

void animate_hind_suspension(object_3d_instance* inst3d);
void animate_apache_suspension(object_3d_instance* inst3d);

void rotate_helicopter_wheels(object_3d_instance* inst3d);

#endif
