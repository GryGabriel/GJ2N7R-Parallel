function getText(input, id){
    fetch('text.txt')
        .then(response => response.text())
        .then(text => {
            const workerCount = 20;
            const textArray = Array.from(text);
            if(id == 'inputFieldEncrypt'){
                encrypt(input, textArray, workerCount)
            }else(
                decrypt(input, text, workerCount)
            )
        })
        .catch(error => {
            console.log('Error reading file:', error);
        });
};