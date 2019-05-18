const { Trader, Mduser } = require('bindings')('ctp')
const mduser = new Mduser()
async function main() {
    await mduser.connect('tcp://180.168.146.187:10010');
    console.log('connected')
}
main();