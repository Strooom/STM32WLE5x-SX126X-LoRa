
function Decoder(bytes, port) {

    var decoded = [];
    var payloadEncodingVersion = bytes[0];
    switch (payloadEncodingVersion) {
        case 0x02: // mumo_v2_0
            for (var i = 1; i < bytes.length;) {
                var measurementChannel = bytes[i];
                var measurementTimestamp = bytes[i + 4] << 24 | bytes[i + 3] << 16 | bytes[i + 2] << 8 | bytes[i + 1];
                var floatValue = bytesToFloat(bytes[i + 5], bytes[i + 6], bytes[i + 7], bytes[i + 8])

                switch (measurementChannel) {
                    case 0x01:
                        decoded.push({
                            field: "BATTERYVOLTAGE",
                            value: floatValue,
                            timestamp: measurementTimestamp
                        });
                        break;

                    case 0x10:
                        decoded.push({
                            field: "TEMPERATURE",
                            value: floatValue,
                            timestamp: measurementTimestamp
                        });
                        break;

                    case 0x11:
                        decoded.push({
                            field: "RELATIVEHUMIDITY",
                            value: floatValue,
                            timestamp: measurementTimestamp
                        });
                        break;

                    case 0x12:
                        decoded.push({
                            field: "BAROMETRICPRESSURE",
                            value: floatValue,
                            //                    timestamp: measurementTimestamp
                        });
                        break;

                    default:
                }
                i += 9;
            }
            break;

        default:
    }
    return decoded;
}

function bytesToFloat(byte1, byte2, byte3, byte4) {
    var bits = byte4 << 24 | byte3 << 16 | byte2 << 8 | byte1;
    var sign = (bits >>> 31 === 0) ? 1.0 : -1.0;
    var e = bits >>> 23 & 0xff;
    var m = (e === 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;
    var f = sign * m * Math.pow(2, e - 150);
    return f;
}


