extends Sprite3D

@onready var animation_player = $AnimationPlayer


func boom():
	show()
	animation_player.play("explode")
	await get_tree().create_timer(5).timeout
	get_tree().quit()
