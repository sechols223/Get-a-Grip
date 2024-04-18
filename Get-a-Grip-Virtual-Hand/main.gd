extends Node

@onready var directional_light_3d = $DirectionalLight3D
@onready var camera_3d = $Camera3D
@onready var close_camera_pos = $CloseCameraPos
@onready var server_address_form = $ServerAddressForm
@onready var kaboom = $Kaboom
@onready var controllable_hand = $ControllableHand
@onready var connecting_label = $ConnectingLabel


var socket = WebSocketPeer.new()

var submitted = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if submitted:
		var lr = Input.get_axis("ui_left", "ui_right")
		var bf = Input.get_axis("ui_up", "ui_down")
		
		camera_3d.position += Vector3(lr, 0, bf).rotated(Vector3.UP, camera_3d.rotation.y) * delta
		
		camera_3d.look_at(Vector3.ZERO)
		
		socket.poll()
		var state = socket.get_ready_state()
		
		match state:
			WebSocketPeer.STATE_CONNECTING:
				connecting_label.show()
			WebSocketPeer.STATE_OPEN:
				connecting_label.hide()
				move_fingers()
			WebSocketPeer.STATE_CLOSING:
				pass
			WebSocketPeer.STATE_CLOSED:
				connecting_label.hide()
				die_lmao()

func move_fingers():
	for i in range(socket.get_available_packet_count()):
		var json_string = socket.get_packet().get_string_from_utf8()
		var json_obj = JSON.parse_string(json_string)
		if json_obj is Dictionary and "finger" in json_obj and "angle" in json_obj:
			controllable_hand.set_finger(json_obj["finger"], json_obj["angle"]/180.0)

func _on_server_address_form_submitted(server_address: String):
	var tween = create_tween().set_parallel()
	tween.tween_property(camera_3d, "transform", close_camera_pos.transform, 1)
	tween.tween_property(camera_3d, "fov", 70, 1)
	tween.tween_property(directional_light_3d, "rotation:x", -PI/4, 3)
	server_address_form.hide()
	socket.connect_to_url(server_address)
	set_deferred("submitted", true)

func die_lmao():
	set_process(false)
	controllable_hand.hide()
	kaboom.boom()
