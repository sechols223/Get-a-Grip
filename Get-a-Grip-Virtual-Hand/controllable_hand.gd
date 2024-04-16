extends Node3D

@export var finger_move_speed = 1.0

@onready var anim_tree = $AnimationTree

var finger_values = {
	"pinky": 0.0,
	"ring": 0.0,
	"middle": 0.0,
	"index": 0.0,
	"thumb": 0.0
}

var finger_targets = {
	"pinky": 0.0,
	"ring": 0.0,
	"middle": 0.0,
	"index": 0.0,
	"thumb": 0.0
}

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	for finger in finger_values:
		finger_values[finger] = \
			move_toward(finger_values[finger], finger_targets[finger], finger_move_speed * delta)
	_update_fingers()

func _update_fingers():
	for finger in finger_values:
		var property_name = "parameters/%sSeek/seek_request" % finger.capitalize()
		anim_tree[property_name] = finger_values[finger]

func set_finger(finger: String, value: float):
	if finger in finger_targets:
		finger_targets[finger] = value
