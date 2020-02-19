SuperStrict

Type TGameSound
	Const NoGunSounds:Int = 5, NoExplosionSounds:Int = 1, NoGunChannels:Int = 4, NoExplosionChannels:Int = 4, NoLargeExplosionChannels:Int = 2
	Field masterVolume:Double = 0
	Field gunSounds:TSound[], channels:TChannel[], explosionChannels:TChannel[], largeExplosionChannels:TChannel[], lastPlay:Long
	Field lastExplosion:Long, explosionSounds:TSound[], lastLargeExplosion:Long
	
	Function Create:TGameSound()
		Local o:TGameSound = New TGameSound
		
		' Sounds
		o.gunSounds = New TSound[NoGunSounds]
		For Local i:Int = 0 To NoGunSounds - 1
			o.gunSounds[i] = LoadSound("Res/Sounds/Gun" + (i + 1) + ".wav", SOUND_HARDWARE)
		Next
		o.explosionSounds = New TSound[NoExplosionSounds]
		For Local i:Int = 0 To NoExplosionSounds - 1
			o.explosionSounds[i] = LoadSound("Res/Sounds/Explosion" + (i + 1) + ".wav", SOUND_HARDWARE)
		Next
		
		' Channels
		o.channels = New TChannel[NoGunChannels]
		For Local i:Int = 0 To NoGunChannels - 1
			o.channels[i] = AllocChannel()
'			SetChannelRate(o.channels[i], 0.125)
		Next
		o.explosionChannels = New TChannel[NoExplosionChannels]
		For Local i:Int = 0 To NoExplosionChannels - 1
			o.explosionChannels[i] = AllocChannel()
'			SetChannelRate(o.explosionChannels[i], 0.25)
		Next
		o.largeExplosionChannels = New TChannel[NoLargeExplosionChannels]
		For Local i:Int = 0 To NoLargeExplosionChannels - 1
			o.largeExplosionChannels[i] = AllocChannel()
'			SetChannelRate(o.largeExplosionChannels[i], 1.0)
		Next
		Return o
	End Function
	
	Method PlayGunSound(i:Int, ms:Long, scale:Double)
		If ms < lastPlay + 100 Then Return 
		
		' Find a channel
		For Local c:TChannel = EachIn channels
			If Not ChannelPlaying(c) Then
				SetChannelVolume(c, scale * masterVolume)
'				PlaySound(gunSounds[i], c)
				lastPlay = ms
				Return
			End If
		Next
	End Method

	Method PlayExplosionSound(i:Int, ms:Long, scale:Double)
		If ms < lastExplosion + 100 Then Return 
		
		' Find a channel
		For Local c:TChannel = EachIn explosionChannels
			If Not ChannelPlaying(c) Then
				SetChannelVolume(c, scale * masterVolume)
				PlaySound(explosionSounds[i], c)
				lastExplosion = ms
				Return
			End If
		Next
	End Method
	
	Method PlayLargeExplosionSound(i:Int, ms:Long, scale:Double)
		If ms < lastLargeExplosion + 100 Then Return 
		
		' Find a channel
		For Local c:TChannel = EachIn largeExplosionChannels
			If Not ChannelPlaying(c) Then
				SetChannelVolume(c, scale)
'				PlaySound(explosionSounds[i], c)
				lastLargeExplosion = ms
				Return
			End If
		Next
	End Method

End Type
