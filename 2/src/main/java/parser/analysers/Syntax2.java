package parser.analysers;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Syntax2 {
    public boolean analyse(List<String> parsedList) {
        boolean result = false;
        for (var i = 0; i < parsedList.toArray().length; i++) {
            System.out.println(parsedList.get(i) + " I");

            String[] split = parsedList.get(i).split("");
            if (Objects.equals(split[i], "{")) {
                for (var j = 0; j < parsedList.get(i).length(); j++) {
                    if (Objects.equals(split[j], "\"")) {
                        j++;
                        // parse the rest of the string
                        while (true) {
                            if (split[j].matches("[A-Za-z0-9]]")) {
                                j++;
                                continue;
                            }
                            if (Objects.equals(split[j], "\"")) {
                                result = true;
                                break;
                            }
                            result = false;
                            break;
                        }
                    }

                    if (Objects.equals(split[j], "}")) {
                        result = true;
                        break;
                    }
//                    result = false;
                }
            }
        }
        return result;
    }
}
