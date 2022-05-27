

var soundManager = {
    clips: {
    },
    context: null,
    gainNode: null, // главный узел
    loaded: false, // все звуки загружены
    init: function (){ // инициализация
        this.context = new AudioContext();
        this.gainNode = this.context.createGain();
        this.gainNode.connect(this.context.destination); // подключение к динамикам
    }, // инициализация менеджера звука
    load: function (path, callback) { // загрузка одного аудиофайла
        if(this.clips[path]){ // проверяем что уже загружены
            callback(this.clips[path]); // вызываем загруженный
            return;
        }
        var clip = {
            path: path,
            buffer: null,
            loaded: false
        }
        clip.play = function (volume, loop) {
            soundManager.play(this.path,{looping: loop ? loop: false, volume: volume ? volume : 1})
        };

        this.clips[path] = clip;
        var request = new XMLHttpRequest();
        request.open('GET',path,true);
        request.responseType='arraybuffer';
        request.onload = function () {
            soundManager.context.decodeAudioData(request.response,
                function (buffer) {
                    clip.buffer = buffer;
                    clip.loaded = true;
                    callback(clip)
                });
        };
        request.send();
    },

    loadArray: function (array){ // загрузить массив звуков
        for(var i =0; i < array.length; i++){
            soundManager.load(array[i], function () {
                if (array.length === Object.keys(soundManager.clips).length){
                    for ( sd in soundManager.clips){
                        if(!soundManager.clips[sd].loaded) return;
                    }
                    soundManager.loaded = true;
                }
            });
        }

    },

    play: function (path, settings) {
        if(!soundManager.loaded){
            console.log('Trying to play');
            setTimeout(function () { soundManager.play(path,settings);}, 1000);
            return;
        }
        var looping = false;
        var volume = 1;
        if(settings){
            if(settings.looping)
                looping = settings.looping
            if(settings.volume)
                volume = settings.volume
        }

        var sd = this.clips[path]; // получаем звуковой эффект
        if(sd === null)
            return false;

        var sound = soundManager.context.createBufferSource();
        sound.buffer = sd.buffer;
        sound.connect(soundManager.gainNode);
        sound.loop = looping;
        soundManager.gainNode.gain.value = volume;
        sound.start(0);
        //console.log("Successfully played");
        return true;
    }// проигрывание файла
};
