extends VBoxContainer

@onready var hand_icon = $HandIconBox/HandIcon
@onready var loading_text = $LoadingText

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	hand_icon.rotation = fmod(hand_icon.rotation + delta * TAU, TAU)

func set_loading_text(new_text: String):
	loading_text.text = new_text
