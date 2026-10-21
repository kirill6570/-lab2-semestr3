package input

import (
	"bufio"
	"os"
)

// One reader shared by the menu and all tasks.
var Reader = bufio.NewReader(os.Stdin)
