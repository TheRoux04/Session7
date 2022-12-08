//Show me exemple of mutex use in go language

/*A mutex is a synchronization mechanism used to control access to a shared
resource in a concurrent program. Here's an example of how to use a mutex in
the Go programming language:*/

package main

import (
	"fmt"
	"sync"
)

// Counter is a simple counter struct.
type Counter struct {
	sync.Mutex
	value int
}

// Inc increments the counter by one.
func (c *Counter) Inc() {
	c.Lock()
	defer c.Unlock()
	c.value++
}

// Value returns the current value of the counter.
func (c *Counter) Value() int {
	c.Lock()
	defer c.Unlock()
	return c.value
}

func main() {
var wg sync.WaitGroup
c := Counter{}

for i := 0; i < 1000; i++ {
	wg.Add(1)
	go func() {
	c.Inc()
	wg.Done()
	}()
}

wg.Wait()
fmt.Println(c.Value())
}

/*In this example, we have a Counter struct that has a mutex and an integer value field.
The Inc method uses the mutex to synchronize access to the value field, locking it before
incrementing the value and unlocking it when it's done. The Value method also uses the mutex to
synchronize access to the value field, locking it before returning the value and unlocking it when it's done.
 */

/*In the main function, we create a new Counter and start 1000 goroutines that concurrently
increment the counter. We use the WaitGroup from the sync package to wait for all goroutines to
finish before printing the final value of the counter. Because the Inc and Value methods use the
mutex to synchronize access to the value field, the final value should always be 1000.
 */

/*I hope this helps! Let me know if you have any other questions.*/


/*Here's another example of how to use a mutex in Go. In this example,
we have a Map struct that represents a simple key-value map. The Map struct has a
mutex and a data map that stores the key-value pairs.
 */

package main

import (
	"fmt"
	"sync"
)

// Map is a simple key-value map.
type Map struct {
	sync.Mutex
	data map[string]string
}

// Set sets the value for a key in the map.
func (m *Map) Set(key, value string) {
	m.Lock()
	defer m.Unlock()
	m.data[key] = value
}

// Get gets the value for a key from the map.
func (m *Map) Get(key string) (string, bool) {
	m.Lock()
	defer m.Unlock()
	value, ok := m.data[key]
	return value, ok
}

func main() {
	var wg sync.WaitGroup
	m := Map{data: make(map[string]string)}

	wg.Add(2)
	go func() {
	m.Set("foo", "bar")
	wg.Done()
	}()
	go func() {
	m.Set("baz", "qux")
	wg.Done()
	}()

	wg.Wait()
	value, ok := m.Get("foo")
	fmt.Println(value, ok)
	value, ok = m.Get("baz")
	fmt.Println(value, ok)
}

/*In this example, the Set and Get methods use the mutex to synchronize access to the data map.
In the main function, we create a new Map and start two goroutines that concurrently set
values in the map. We use the WaitGroup from the sync package to wait for both goroutines
to finish before getting the values for the "foo" and "baz" keys. Because the Set and Get
methods use the mutex to synchronize access to the data map, the final values should always be "bar" and "qux".

I hope this helps! Let me know if you have any other questions.*/
